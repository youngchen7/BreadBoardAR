//
// DirectXPage.xaml.cpp
// Implementation of the DirectXPage class.
//

#include "pch.h"
#include "DirectXPage.xaml.h"
#include "StarterKitMain.h"

#include <opencv2\core\core.hpp>



using namespace StarterKit;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::System::Threading;
using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace concurrency;

DirectXPage::DirectXPage() :
m_windowVisible(true)
{
	InitializeComponent();

	Windows::UI::ViewManagement::StatusBar::GetForCurrentView()->HideAsync();

	// Register event handlers for page lifecycle.
	CoreWindow^ window = Window::Current->CoreWindow;

	window->VisibilityChanged +=
		ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &DirectXPage::OnVisibilityChanged);

	DisplayInformation^ currentDisplayInformation = DisplayInformation::GetForCurrentView();

	currentDisplayInformation->DpiChanged +=
		ref new TypedEventHandler<DisplayInformation^, Object^>(this, &DirectXPage::OnDpiChanged);

	currentDisplayInformation->OrientationChanged +=
		ref new TypedEventHandler<DisplayInformation^, Object^>(this, &DirectXPage::OnOrientationChanged);

	DisplayInformation::DisplayContentsInvalidated +=
		ref new TypedEventHandler<DisplayInformation^, Object^>(this, &DirectXPage::OnDisplayContentsInvalidated);

	swapChainPanel->CompositionScaleChanged +=
		ref new TypedEventHandler<SwapChainPanel^, Object^>(this, &DirectXPage::OnCompositionScaleChanged);

	swapChainPanel->SizeChanged +=
		ref new SizeChangedEventHandler(this, &DirectXPage::OnSwapChainPanelSizeChanged);

	// At this point we have access to the device. 
	// We can create the device-dependent resources.
	m_deviceResources = std::make_shared<DX::DeviceResources>();
	m_deviceResources->SetSwapChainPanel(swapChainPanel);

	m_main = std::unique_ptr<StarterKitMain>(new StarterKitMain(m_deviceResources, Preview));
	m_main->StartRenderLoop(Preview->Width, Preview->Height);

	

	//Set up our popup windows
	circuits_window->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	schematic_window->Visibility = Windows::UI::Xaml::Visibility::Collapsed;



}

DirectXPage::~DirectXPage()
{
	// Stop rendering and processing events on destruction.
	m_main->StopRenderLoop();
}



// Saves the current state of the app for suspend and terminate events.
void DirectXPage::SaveInternalState(IPropertySet^ state)
{
	critical_section::scoped_lock lock(m_main->GetCriticalSection());
	m_deviceResources->Trim();

	// Stop rendering when the app is suspended.
	m_main->StopRenderLoop();

	// Put code to save app state here.
}

// Loads the current state of the app for resume events.
void DirectXPage::LoadInternalState(IPropertySet^ state)
{
	// Put code to load app state here.

	// Start rendering when the app is resumed.
	m_main->StartRenderLoop();
}

// Called when the SwapChainPanel is tapped.
void DirectXPage::OnTapped(Object^ sender, TappedRoutedEventArgs^ e)
{
	auto currentPoint = e->GetPosition(nullptr);
	String^ objName = m_main->OnHitObject((int)(currentPoint.X * swapChainPanel->CompositionScaleX), (int)(currentPoint.Y * swapChainPanel->CompositionScaleY));
	if (objName != nullptr)
	{
		m_main->ToggleHitEffect(objName);

	}
}



// Window event handlers.

void DirectXPage::OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args)
{
	m_windowVisible = args->Visible;
	if (m_windowVisible)
	{
		m_main->StartRenderLoop();
	}
	else
	{
		m_main->StopRenderLoop();
	}
}

// DisplayInformation event handlers.

void DirectXPage::OnDpiChanged(DisplayInformation^ sender, Object^ args)
{
	OutputDebugString(L"SwapChainPanel dpi changed");
	critical_section::scoped_lock lock(m_main->GetCriticalSection());
	m_deviceResources->SetDpi(sender->LogicalDpi);
	m_main->CreateWindowSizeDependentResources();
}

void DirectXPage::OnOrientationChanged(DisplayInformation^ sender, Object^ args)
{
	OutputDebugString(L"SwapChainPanel orientation changed");
	critical_section::scoped_lock lock(m_main->GetCriticalSection());
	m_deviceResources->SetCurrentOrientation(sender->CurrentOrientation);
	m_main->CreateWindowSizeDependentResources();
}

void DirectXPage::OnDisplayContentsInvalidated(DisplayInformation^ sender, Object^ args)
{
	OutputDebugString(L"SwapChainPanel display contents invalidated changed");
	critical_section::scoped_lock lock(m_main->GetCriticalSection());
	m_deviceResources->ValidateDevice();
}

void DirectXPage::OnCompositionScaleChanged(SwapChainPanel^ sender, Object^ args)
{
	OutputDebugString(L"SwapChainPanel composition scale changed");
	critical_section::scoped_lock lock(m_main->GetCriticalSection());
	m_deviceResources->SetCompositionScale(sender->CompositionScaleX, sender->CompositionScaleY);
	m_main->CreateWindowSizeDependentResources();
}

void DirectXPage::OnSwapChainPanelSizeChanged(Object^ sender, SizeChangedEventArgs^ e)
{
	OutputDebugString(L"SwapChainPanel size changed");
	critical_section::scoped_lock lock(m_main->GetCriticalSection());
	m_deviceResources->SetLogicalSize(e->NewSize);
	m_main->CreateWindowSizeDependentResources();
}



void StarterKit::DirectXPage::schematics_btn_click(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{	
	if (schematic_window->Visibility == Windows::UI::Xaml::Visibility::Visible)
	{
		schematic_window->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	}
	else
	{
		schematic_window->Visibility = Windows::UI::Xaml::Visibility::Visible;
		circuits_window->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	}
}


void StarterKit::DirectXPage::circuits_btn_click(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
	if (circuits_window->Visibility == Windows::UI::Xaml::Visibility::Visible)
	{
		circuits_window->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	}
	else
	{
		circuits_window->Visibility = Windows::UI::Xaml::Visibility::Visible;
		schematic_window->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	}
}
