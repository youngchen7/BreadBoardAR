// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved

#pragma once

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "Content\SampleFpsTextRenderer.h"
#include "Game.h"

#include <aruco.h>
#include <cvdrawingutils.h>
#include <opencv2\highgui\cap_winrt\WinRTVideoCapture.h>


// Renders Direct2D and 3D content on the screen.
namespace StarterKit
{
	class StarterKitMain : public DX::IDeviceNotify
	{
	public:
		StarterKitMain(const std::shared_ptr<DX::DeviceResources>& deviceResources, Windows::UI::Xaml::Controls::Image^ image);
		~StarterKitMain();

		// Public methods passed straight to the Game renderer.
		Platform::String^ OnHitObject(int x, int y) { return m_sceneRenderer->OnHitObject(x, y); }
		void ToggleHitEffect(Platform::String^ object) { m_sceneRenderer->ToggleHitEffect(object); }
		void ChangeMaterialColor(Platform::String^ object, float r, float g, float b) { m_sceneRenderer->ChangeMaterialColor(object, r, g, b); }
		void setBuild(int ID) { m_sceneRenderer->setBuild(ID); }
		void nextStep(){ m_sceneRenderer->nextStep(); }
		void previousStep(){ m_sceneRenderer->previousStep(); }
		int getStep(){ return m_sceneRenderer->getStep(); }
		int getMaxStep(){ return m_sceneRenderer->getMaxStep(); }
		String^ getDescription() { return m_sceneRenderer->getDescription(); }

		void CreateWindowSizeDependentResources();
		void StartRenderLoop(int width, int height);
		void StartRenderLoop();
		void StopRenderLoop();
		Concurrency::critical_section& GetCriticalSection() { return m_criticalSection; }

		// IDeviceNotify
		virtual void OnDeviceLost();
		virtual void OnDeviceRestored();

	private:
		void Update();
		bool Render();
		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// TODO: Replace with your own content renderers.
		std::unique_ptr<Game> m_sceneRenderer;
		std::unique_ptr<SampleFpsTextRenderer> m_fpsTextRenderer;

		Windows::Foundation::IAsyncAction^ m_renderLoopWorker;
		Concurrency::critical_section m_criticalSection;

		// Rendering loop timer.
		DX::StepTimer m_timer;

		//Image Processing
		Windows::UI::Xaml::Media::Imaging::WriteableBitmap^ m_bitmap;
		HWinRTVideoCapture m_capture;
		unsigned int m_width;
		unsigned int m_height;
		Windows::UI::Xaml::Controls::Image^ m_image;
		aruco::MarkerDetector m_mdetector;
		vector<aruco::Marker> m_markers; 
		aruco::CameraParameters camParam;
		DirectX::XMMATRIX mirror = { (float)-1, (float)0, (float)0, (float)0,
									(float)0, (float)1, (float)0, (float)0,
									(float)0, (float)0, (float)1, (float)0,
									(float)0, (float)0, (float)0, (float)1 };
		DirectX::XMMATRIX offset = { (float)1, (float)0, (float)0, (float)0,
									(float)0, (float)1, (float)0, (float)0,
									(float)0, (float)0, (float)1, (float)0,
									(float)3, (float)0, (float)0, (float)1 };

		//3D Model Position
		
	};
}