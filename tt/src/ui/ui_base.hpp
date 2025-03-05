#pragma once
#include <d3d11.h>
#include "../../ext/imGui 1.19.8/imgui.h"
#include "../../ext/imGui 1.19.8/imgui_impl_dx11.h"
#include "../../ext/imGui 1.19.8/imgui_impl_win32.h"

class UIBase {
public:
    UIBase() : device(nullptr), device_context(nullptr), window(nullptr), menu_visible(false) {}
    virtual ~UIBase() = default;

    // Initialize UI components
    virtual bool Initialize(ID3D11Device* device, ID3D11DeviceContext* device_context, HWND window) {
        this->device = device;
        this->device_context = device_context;
        this->window = window;
        return true;
    }

    virtual void Shutdown() {
        device = nullptr;
        device_context = nullptr;
        window = nullptr;
    }

    // Render functions
    virtual void BeginRender() = 0;
    virtual void EndRender() = 0;
    virtual void RenderMenu() = 0;

    // Menu state
    bool IsMenuVisible() const { return menu_visible; }
    void ToggleMenu() { menu_visible = !menu_visible; }

    // Feature states - Add these virtual functions
    virtual bool IsESPEnabled() const { return false; }
    virtual bool IsTracerEnabled() const { return false; }
    virtual bool IsNoClipEnabled() const { return false; }
    virtual bool IsAimbotEnabled() const { return false; }
    virtual float GetAimbotFOV() const { return 0.0f; }

protected:
    ID3D11Device* device;
    ID3D11DeviceContext* device_context;
    HWND window;
    bool menu_visible;
};