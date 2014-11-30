﻿

//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#include "pch.h"
#include "DirectXPage.xaml.h"




void ::StarterKit::DirectXPage::InitializeComponent()
{
    if (_contentLoaded)
        return;

    _contentLoaded = true;

    // Call LoadComponent on ms-appx:///DirectXPage.xaml
    ::Windows::UI::Xaml::Application::LoadComponent(this, ref new ::Windows::Foundation::Uri(L"ms-appx:///DirectXPage.xaml"), ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);

    // Get the SwapChainPanel named 'swapChainPanel'
    swapChainPanel = safe_cast<::Windows::UI::Xaml::Controls::SwapChainPanel^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"swapChainPanel"));
    // Get the Border named 'circuits_window'
    circuits_window = safe_cast<::Windows::UI::Xaml::Controls::Border^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"circuits_window"));
    // Get the Border named 'schematic_window'
    schematic_window = safe_cast<::Windows::UI::Xaml::Controls::Border^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"schematic_window"));
    // Get the Image named 'schematic_img'
    schematic_img = safe_cast<::Windows::UI::Xaml::Controls::Image^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"schematic_img"));
    // Get the ListView named 'circuits_list'
    circuits_list = safe_cast<::Windows::UI::Xaml::Controls::ListView^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"circuits_list"));
    // Get the Button named 'circuits_select'
    circuits_select = safe_cast<::Windows::UI::Xaml::Controls::Button^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"circuits_select"));
    // Get the Button named 'circuits_cancel'
    circuits_cancel = safe_cast<::Windows::UI::Xaml::Controls::Button^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"circuits_cancel"));
    // Get the Button named 'schematics_btn'
    schematics_btn = safe_cast<::Windows::UI::Xaml::Controls::Button^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"schematics_btn"));
    // Get the Button named 'next_btn'
    next_btn = safe_cast<::Windows::UI::Xaml::Controls::Button^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"next_btn"));
    // Get the Button named 'prev_btn'
    prev_btn = safe_cast<::Windows::UI::Xaml::Controls::Button^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"prev_btn"));
    // Get the Button named 'circuits_btn'
    circuits_btn = safe_cast<::Windows::UI::Xaml::Controls::Button^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"circuits_btn"));
    // Get the TextBlock named 'progress_percent'
    progress_percent = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"progress_percent"));
    // Get the ProgressBar named 'progress_bar'
    progress_bar = safe_cast<::Windows::UI::Xaml::Controls::ProgressBar^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"progress_bar"));
    // Get the TextBlock named 'progress_fraction'
    progress_fraction = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"progress_fraction"));
}

void ::StarterKit::DirectXPage::Connect(int connectionId, Platform::Object^ target)
{
    switch (connectionId)
    {
    case 1:
        (safe_cast<::Windows::UI::Xaml::UIElement^>(target))->Tapped +=
            ref new ::Windows::UI::Xaml::Input::TappedEventHandler(this, (void (::StarterKit::DirectXPage::*)(Platform::Object^, Windows::UI::Xaml::Input::TappedRoutedEventArgs^))&DirectXPage::OnTapped);
        break;
    case 2:
        (safe_cast<::Windows::UI::Xaml::UIElement^>(target))->Tapped +=
            ref new ::Windows::UI::Xaml::Input::TappedEventHandler(this, (void (::StarterKit::DirectXPage::*)(Platform::Object^, Windows::UI::Xaml::Input::TappedRoutedEventArgs^))&DirectXPage::schematics_btn_click);
        break;
    case 3:
        (safe_cast<::Windows::UI::Xaml::UIElement^>(target))->Tapped +=
            ref new ::Windows::UI::Xaml::Input::TappedEventHandler(this, (void (::StarterKit::DirectXPage::*)(Platform::Object^, Windows::UI::Xaml::Input::TappedRoutedEventArgs^))&DirectXPage::circuits_btn_click);
        break;
    }
    (void)connectionId; // Unused parameter
    (void)target; // Unused parameter
    _contentLoaded = true;
}

