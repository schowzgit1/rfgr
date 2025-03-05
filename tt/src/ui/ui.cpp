#include "ui.h"
#include "../random/noclip.h"
#include <dwmapi.h>
#include <stdio.h>
#include "../game/game.h"
#include "../mem/memify.h"
#include "../window/window.hpp"
#include "../math/math.h"
#include "../../ext/imGui 1.19.8/imgui.h"
#include "../../ext/imGui 1.19.8/imgui_impl_win32.h"
#include "../../ext/imGui 1.19.8/imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

UI::UI() : UIBase() {
    device = nullptr;
    device_context = nullptr;   
    window = nullptr;
    menu_visible = false;
    aimbot_enabled = false;
    aimbot_fov = 5.0f;
    esp_enabled = false;
    noclip_enabled = false;
    tracer_enabled = false;
}

UI::~UI() {
    Shutdown();
}

bool UI::Initialize(ID3D11Device* dev, ID3D11DeviceContext* dev_context, HWND win) {
    if (!dev || !dev_context || !win) {
        printf("[>>] Invalid parameters passed to UI::Initialize\n");
        return false;
    }

    device = dev;
    device_context = dev_context;
    window = win;

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup custom style with modern look
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 10.0f;
    style.FrameRounding = 6.0f;
    style.PopupRounding = 6.0f;
    style.ScrollbarRounding = 6.0f;
    style.GrabRounding = 6.0f;
    style.TabRounding = 6.0f;
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.ItemSpacing = ImVec2(8, 8);
    style.ItemInnerSpacing = ImVec2(8, 6);
    style.IndentSpacing = 25.0f;
    style.ScrollbarSize = 15.0f;
    style.GrabMinSize = 10.0f;

    // Modern color scheme
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.95f);
    colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.13f, 0.13f, 0.17f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.19f, 0.19f, 0.25f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.24f, 0.24f, 0.32f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.13f, 0.13f, 0.17f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.25f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.24f, 0.24f, 0.32f, 1.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.13f, 0.13f, 0.17f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.25f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.24f, 0.24f, 0.32f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.13f, 0.13f, 0.17f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.19f, 0.19f, 0.25f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.24f, 0.24f, 0.32f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.13f, 0.13f, 0.17f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.24f, 0.24f, 0.32f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.13f, 0.13f, 0.17f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.24f, 0.24f, 0.32f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.13f, 0.13f, 0.17f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.13f, 0.17f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.24f, 0.24f, 0.32f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.24f, 0.24f, 0.32f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.24f, 0.24f, 0.32f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.24f, 0.24f, 0.32f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.24f, 0.32f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.24f, 0.24f, 0.32f, 1.00f);

    // Initialize ImGui Win32
    if (!ImGui_ImplWin32_Init(window)) {
        printf("[>>] Failed ImGui_ImplWin32_Init\n");
        return false;
    }

    // Initialize ImGui DirectX 11
    if (!ImGui_ImplDX11_Init(device, device_context)) {
        printf("[>>] Failed ImGui_ImplDX11_Init\n");
        ImGui_ImplWin32_Shutdown();
        return false;
    }

    return true;
}

void UI::Shutdown() {
    if (device && device_context) {
        // Cleanup ImGui
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }

    device = nullptr;
    device_context = nullptr;
    window = nullptr;
}

void UI::BeginRender() {
    if (!device || !device_context || !window) {
        return;
    }

    // Handle Windows messages
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Begin a new frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void UI::EndRender() {
    if (!device || !device_context) {
        return;
    }

    ImGui::Render();
}

void UI::RenderMenu() {
    if (!menu_visible || !device || !device_context) {
        return;
    }

    // Set window size and position
    ImGui::SetNextWindowSize({ 350, 400 }, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos({ 50, 50 }, ImGuiCond_FirstUseEver);

    // Add window flags for modern look
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoCollapse;

    // Begin window with custom title
    ImGui::Begin("FiveM Menu", &menu_visible, window_flags);

    // Add some spacing at the top
    ImGui::Spacing();
    ImGui::Spacing();

    // Add a header with custom styling
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("FIVEM MENU").x) * 0.5f);
    ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "FIVEM MENU");
    ImGui::PopFont();

    ImGui::Separator();

    // Add tabs with custom styling and animations
    if (ImGui::BeginTabBar("Features", ImGuiTabBarFlags_FittingPolicyScroll)) {
        if (ImGui::BeginTabItem("Aimbot")) {
            RenderAimbotSettings();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("ESP")) {
            RenderESPSettings();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Misc")) {
            RenderMiscSettings();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    ImGui::End();
}

void UI::RenderAimbotSettings() {
    ImGui::Spacing();

    // Add a group for Aimbot settings
    ImGui::BeginGroup();

    // Add a header for the section
    ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Aimbot Configuration");
    ImGui::Separator();

    // Add some spacing
    ImGui::Spacing();

    // Enable checkbox with custom styling
    ImGui::Checkbox("Enable Aimbot", &aimbot_enabled);

    if (aimbot_enabled) {
        ImGui::Spacing();
        ImGui::Text("FOV Settings");
        ImGui::SliderFloat("FOV", &aimbot_fov, 1.0f, 180.0f, "%.1f°");
    }

    ImGui::EndGroup();
}

void UI::RenderESPSettings() {
    ImGui::Spacing();

    // Add a group for ESP settings
    ImGui::BeginGroup();

    // Add a header for the section
    ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "ESP Configuration");
    ImGui::Separator();

    // Add some spacing
    ImGui::Spacing();

    // Enable checkbox with custom styling
    ImGui::Checkbox("Enable ESP", &esp_enabled);

    if (esp_enabled) {
        ImGui::Spacing();
        ImGui::Checkbox("Enable Tracers", &tracer_enabled);
        // Add more ESP settings here
    }

    ImGui::EndGroup();
}

void UI::RenderMiscSettings() {
    ImGui::Spacing();

    // Add a group for Misc settings
    ImGui::BeginGroup();

    // Add a header for the section
    ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Miscellaneous Options");
    ImGui::Separator();

    // Add some spacing
    ImGui::Spacing();

    // Enable checkbox with custom styling
    ImGui::Checkbox("Enable NoClip(comming soon)", &noclip_enabled);

    if (noclip_enabled) {
        ImGui::Spacing();
        ImGui::Text("NoClip Controls");
        ImGui::Text("Up/Down Arrows: Move Forward/Backward");
        ImGui::Text("Left/Right Arrows: Strafe Left/Right");
        ImGui::Text("E/Q: Move Up/Down");
        ImGui::Text("A/D: Look Left/Right");
        ImGui::Text("Speed: %.1f", 0.5f); // Match the speed in noclip.cpp

        // Run NoClip when enabled
       // FiveM::Random::RunNoClip(mem, true);
    }

    ImGui::EndGroup();
}