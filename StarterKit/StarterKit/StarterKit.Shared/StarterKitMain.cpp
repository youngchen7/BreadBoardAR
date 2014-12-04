// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved

#include "pch.h"
#include "StarterKitMain.h"
#include "Common\DirectXHelper.h"
#include <sstream>

using namespace StarterKit;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Concurrency;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Microsoft::WRL;
using namespace Windows::Media::MediaProperties;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::Storage::Streams;


#include <opencv2\highgui\cap_winrt\WinRTVideoCapture.h>
#include <opencv2\imgproc\types_c.h>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>

static const int sWidth = 960;//640;
static const int sHeight = 540;//360;

// Loads and initializes application assets when the application is loaded.
StarterKitMain::StarterKitMain(const std::shared_ptr<DX::DeviceResources>& deviceResources, Windows::UI::Xaml::Controls::Image^ image) :
m_deviceResources(deviceResources)
, m_image(image)
, m_width(sWidth)
, m_height(sHeight)
{
	// Register to be notified if the Device is lost or recreated
	m_deviceResources->RegisterDeviceNotify(this);

	// TODO: Replace this with your app's content initialization.
	m_sceneRenderer = std::unique_ptr<Game>(new Game(m_deviceResources));

	m_fpsTextRenderer = std::unique_ptr<SampleFpsTextRenderer>(new SampleFpsTextRenderer(m_deviceResources));

	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/
	image->Width = sWidth;
	image->Height = sHeight;

	
	cv::Mat camMatrix = (cv::Mat_<double>(3, 3)
		<< 6.57591187e+002, 0, 3.16504272e+002, 0, 6.60952637e+002, 2.27605789 + 002, 0, 0, 1);

	cv::Mat camDistortion = (cv::Mat_<double>(1, 4)
		<< -1.49060376e-002, 2.05916256e-001, -5.76808210e-003, -8.43471102e-002);
	cv::Size camSize(sWidth, sHeight) ;
	camParam.setParams(camMatrix, camDistortion, camSize);

}

StarterKitMain::~StarterKitMain()
{
	// Deregister device notification
	m_deviceResources->RegisterDeviceNotify(nullptr);
}

// Updates application state when the window size changes (e.g. device orientation change)
void StarterKitMain::CreateWindowSizeDependentResources()
{
	// TODO: Replace this with the size-dependent initialization of your app's content.
	m_sceneRenderer->CreateWindowSizeDependentResources();
}

inline void ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr))
	{
		throw Exception::CreateException(hr);
	}
}
// Helper function to get pointer to WriteableBitmap pixel buffer
byte* GetPointerToPixelData(IBuffer^ buffer)
{
	// Cast to Object^, then to its underlying IInspectable interface.
	Object^ obj = buffer;
	ComPtr<IInspectable> insp(reinterpret_cast<IInspectable*>(obj));

	// Query the IBufferByteAccess interface.
	ComPtr<IBufferByteAccess> bufferByteAccess;
	ThrowIfFailed(insp.As(&bufferByteAccess));

	// Retrieve the buffer data.
	byte* pixels = nullptr;
	ThrowIfFailed(bufferByteAccess->Buffer(&pixels));
	return pixels;
}
void StarterKitMain::StartRenderLoop(int width, int height)
{
	m_width = width;
	m_height = height;
	StartRenderLoop();
}
void StarterKitMain::StartRenderLoop()
{
	// If the animation render loop is already running then do not start another thread.
	if (m_renderLoopWorker != nullptr && m_renderLoopWorker->Status == Windows::Foundation::AsyncStatus::Started)
	{
		return;
	}

	// Create a task that will be run on a background thread.
	auto workItemHandler = ref new WorkItemHandler([this](IAsyncAction ^ action)
	{
		// Calculate the updated frame and render once per vertical blanking interval.
		while (action->Status == Windows::Foundation::AsyncStatus::Started)
		{
			critical_section::scoped_lock lock(m_criticalSection);
			Update();
			if (Render())
			{
				m_deviceResources->Present();
			}
		}
	});

	// Run task on a dedicated high priority background thread.
	m_renderLoopWorker = ThreadPool::RunAsync(workItemHandler, WorkItemPriority::High, WorkItemOptions::TimeSliced);
	m_bitmap = ref new WriteableBitmap(m_width, m_height);

	// create the Video Capture device
	m_capture = WinRTVideoCapture::create(m_width, m_height);

	// start capturing video. Callback will happen on the UI thread
	m_capture->start([this](const cv::Mat& mat) {

		using namespace cv;
		// convert to grayscale
		//Mat output = mat.clone();
		Mat intermediate;
		cvtColor(mat, intermediate, CV_RGB2GRAY);
		Mat output = mat.clone();
		//aruco::MarkerDetector MDetector;
		//vector<aruco::Marker> Markers;

		m_mdetector.detect(intermediate, m_markers, camParam, 0.05f, false);

		for (unsigned int i = 0; i < m_markers.size(); i++) {
			m_markers[i].draw(output, Scalar(0, 0, 255), 2);
			if (m_markers[i].id == 10)
			{
				/*
				Mat Rot;
				Rodrigues(m_markers[i].Rvec, Rot);
				DirectX::XMMATRIX universal_transform = {	Rot.at<float>(0, 0), Rot.at<float>(0, 1), Rot.at<float>(0, 2), 0,
															Rot.at<float>(1, 0), Rot.at<float>(1, 1), Rot.at<float>(1, 2), 0,
															Rot.at<float>(2, 0), Rot.at<float>(2, 1), Rot.at<float>(2, 2), 0,
															0, 0, 0, 1 };
				m_sceneRenderer->setUniversalTransform(universal_transform);

				wstringstream ws;

				ws << L"Marker Transform Matrix: " << endl <<
					Rot.at<float>(0, 0) << " " << Rot.at<float>(0, 1) << " " << Rot.at<float>(0, 2) << " " << m_markers[i].Tvec.at<float>(0) << endl <<
					Rot.at<float>(1, 0) << " " << Rot.at<float>(1, 1) << " " << Rot.at<float>(1, 2) << " " << m_markers[i].Tvec.at<float>(1) << endl <<
					Rot.at<float>(2, 0) << " " << Rot.at<float>(2, 1) << " " << Rot.at<float>(2, 2) << " " << m_markers[i].Tvec.at<float>(2) << endl;

				OutputDebugString(ws.str().c_str());
				*/
				double transform_matrix[16];
				m_markers[i].glGetModelViewMatrix(transform_matrix);

				DirectX::XMMATRIX universal_transform = {	(float)transform_matrix[0], (float)transform_matrix[1], (float)transform_matrix[1], (float)transform_matrix[3],
															(float)transform_matrix[4], (float)transform_matrix[5], (float)transform_matrix[6], (float)transform_matrix[7],
															(float)transform_matrix[8], (float)transform_matrix[9], (float)transform_matrix[10], (float)transform_matrix[11],
															(float)transform_matrix[12], (float)transform_matrix[13], (float)transform_matrix[14], (float)transform_matrix[15] };
				m_sceneRenderer->setUniversalTransform(universal_transform);

			}
		}



		// convert to BGRA
		//cvtColor(intermediate, output, CV_GRAY2BGRA);

		// copy processed image into the WriteableBitmap
		memcpy(GetPointerToPixelData(m_bitmap->PixelBuffer), output.data, m_width * m_height * 4);

		// display the image
		m_image->Source = m_bitmap;
		m_bitmap->Invalidate();
	});
}

void StarterKitMain::StopRenderLoop()
{
	m_renderLoopWorker->Cancel();
}

// Updates the application state once per frame.
void StarterKitMain::Update()
{
	// Update scene objects.
	m_timer.Tick([&]()
	{
		// TODO: Replace this with your app's content update functions.
		m_sceneRenderer->Update(m_timer);
		m_fpsTextRenderer->Update(m_timer);
	});
}

// Renders the current frame according to the current application state.
// Returns true if the frame was rendered and is ready to be displayed.
bool StarterKitMain::Render()
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return false;
	}

	auto context = m_deviceResources->GetD3DDeviceContext();

	// Reset the viewport to target the whole screen.
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	// Reset render targets to the screen.
	ID3D11RenderTargetView *const targets[1] = { m_deviceResources->GetBackBufferRenderTargetView() };
	context->OMSetRenderTargets(1, targets, m_deviceResources->GetDepthStencilView());

	// Clear the back buffer and depth stencil view.
	context->ClearRenderTargetView(m_deviceResources->GetBackBufferRenderTargetView(), DirectX::Colors::Transparent);
	context->ClearDepthStencilView(m_deviceResources->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// Render the scene objects.
	m_sceneRenderer->Render();
	m_fpsTextRenderer->Render();

	return true;
}

// Notifies renderers that device resources need to be released.
void StarterKitMain::OnDeviceLost()
{
	m_sceneRenderer->ReleaseDeviceDependentResources();
	m_fpsTextRenderer->ReleaseDeviceDependentResources();
}

// Notifies renderers that device resources may now be recreated.
void StarterKitMain::OnDeviceRestored()
{
	m_sceneRenderer->CreateDeviceDependentResources();
	m_fpsTextRenderer->CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}