#pragma once
#include <d3d11.h>
#include "../../ext/imGui 1.19.8/imgui.h"
#include "../../ext/imGui 1.19.8/imgui_impl_dx11.h"
#include "../../ext/imGui 1.19.8/imgui_impl_win32.h"
#include "../game/game.h"
#include "ui_base.hpp"

class UI : public UIBase {
public:
    UI();
    ~UI() override;

    // Initialize UI components
    bool Initialize(ID3D11Device* device, ID3D11DeviceContext* device_context, HWND window) override;
    void Shutdown() override;

    // Render functions
    void BeginRender() override;
    void EndRender() override;
    void RenderMenu() override;

    // Menu state
    bool IsMenuVisible() const { return menu_visible; }
    void ToggleMenu() { menu_visible = !menu_visible; }

    // Feature states - Override the virtual functions
    bool IsESPEnabled() const override { return esp_enabled; }
    bool IsTracerEnabled() const override { return tracer_enabled; }
    bool IsNoClipEnabled() const override { return noclip_enabled; }
    bool IsAimbotEnabled() const override { return aimbot_enabled; }
    float GetAimbotFOV() const override { return aimbot_fov; }

private:
    ID3D11Device* device;
    ID3D11DeviceContext* device_context;
    HWND window;
    bool menu_visible;
    
    // Menu state variables
    bool aimbot_enabled;
    float aimbot_fov;
    bool esp_enabled;
    bool noclip_enabled;
    bool tracer_enabled;
    
    // Helper functions
    void RenderAimbotSettings();
    void RenderESPSettings();
    void RenderMiscSettings();
}; 