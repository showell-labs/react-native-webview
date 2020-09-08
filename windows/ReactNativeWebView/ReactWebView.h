// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "winrt/Microsoft.ReactNative.h"
#include "NativeModules.h"
#include "ReactWebView.g.h"

#include "winrt/WebViewBridgeComponent.h"

using namespace winrt::WebViewBridgeComponent;

namespace winrt::ReactNativeWebView::implementation {

    class ReactWebView : public ReactWebViewT<ReactWebView> {
    public:
        ReactWebView(Microsoft::ReactNative::IReactContext const& reactContext);
        void PostMessage(winrt::hstring const& message);
        void SetMessagingEnabled(bool enabled);
        ~ReactWebView();

    private:
        bool m_messagingEnabled{ true };
        winrt::Windows::UI::Xaml::Controls::WebView m_webView{ nullptr };
        Microsoft::ReactNative::IReactContext m_reactContext{ nullptr };
        WebBridge m_webBridge{ nullptr };
        winrt::event_token m_message_token;
        winrt::Windows::UI::Xaml::Controls::WebView::NavigationStarting_revoker m_navigationStartingRevoker{};
        winrt::Windows::UI::Xaml::Controls::WebView::NavigationCompleted_revoker m_navigationCompletedRevoker{};
        winrt::Windows::UI::Xaml::Controls::WebView::NavigationFailed_revoker m_navigationFailedRevoker{};
        winrt::Windows::UI::Xaml::Controls::WebView::PermissionRequested_revoker m_permissionReguestRevoker{};

        void RegisterEvents();
        void WriteWebViewNavigationEventArg(winrt::Windows::UI::Xaml::Controls::WebView const& sender, winrt::Microsoft::ReactNative::IJSValueWriter const& eventDataWriter);
        void OnNavigationStarting(winrt::Windows::UI::Xaml::Controls::WebView const& sender, winrt::Windows::UI::Xaml::Controls::WebViewNavigationStartingEventArgs const& args);
        void OnNavigationCompleted(winrt::Windows::UI::Xaml::Controls::WebView const& sender, winrt::Windows::UI::Xaml::Controls::WebViewNavigationCompletedEventArgs const& args);
        void OnNavigationFailed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::WebViewNavigationFailedEventArgs const& args);
        void OnPremissionRequested(winrt::Windows::UI::Xaml::Controls::WebView const& webView, winrt::Windows::UI::Xaml::Controls::WebViewPermissionRequestedEventArgs const& args);
        void OnMessagePosted(hstring const& message);
    };
} // namespace winrt::ReactNativeWebView::implementation

namespace winrt::ReactNativeWebView::factory_implementation {
    struct ReactWebView : ReactWebViewT<ReactWebView, implementation::ReactWebView> {};
} // namespace winrt::ReactNativeWebView::factory_implementation