﻿

#pragma once
//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------

namespace Windows {
    namespace UI {
        namespace Xaml {
            namespace Controls {
                ref class Image;
                ref class SwapChainPanel;
                ref class Border;
                ref class ListView;
                ref class Button;
                ref class TextBlock;
                ref class ProgressBar;
            }
        }
    }
}

namespace StarterKit
{
    partial ref class DirectXPage : public ::Windows::UI::Xaml::Controls::Page, 
        public ::Windows::UI::Xaml::Markup::IComponentConnector
    {
    public:
        void InitializeComponent();
        virtual void Connect(int connectionId, ::Platform::Object^ target);
    
    private:
        bool _contentLoaded;
    
        private: ::Windows::UI::Xaml::Controls::Image^ Preview;
        private: ::Windows::UI::Xaml::Controls::SwapChainPanel^ swapChainPanel;
        private: ::Windows::UI::Xaml::Controls::Border^ circuits_window;
        private: ::Windows::UI::Xaml::Controls::Border^ schematic_window;
        private: ::Windows::UI::Xaml::Controls::Image^ schematic_img;
        private: ::Windows::UI::Xaml::Controls::ListView^ circuits_list;
        private: ::Windows::UI::Xaml::Controls::Button^ circuits_select;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ circuits_selected;
        private: ::Windows::UI::Xaml::Controls::Button^ circuits_cancel;
        private: ::Windows::UI::Xaml::Controls::Button^ schematics_btn;
        private: ::Windows::UI::Xaml::Controls::Button^ next_btn;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ description_text;
        private: ::Windows::UI::Xaml::Controls::Button^ prev_btn;
        private: ::Windows::UI::Xaml::Controls::Button^ circuits_btn;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ progress_percent;
        private: ::Windows::UI::Xaml::Controls::ProgressBar^ progress_bar;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ progress_fraction;
    };
}

