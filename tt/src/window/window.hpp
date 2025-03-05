#pragma once
#include <d3d11.h>
#include "../../ext/imGui 1.19.8/imgui.h"
#include "../../ext/imGui 1.19.8/imgui_impl_dx11.h"
#include "../../ext/imGui 1.19.8/imgui_impl_win32.h"
#include "../ui/ui_base.hpp"
#include "../ui/ui.h"

// Forward declare UI class to avoid circular dependency
class UI;

class Overlay {
private:
	// creation of device, window, and ImGui.
	bool CreateDevice();
	void CreateOverlay(const char* window_name);
	bool CreateImGui();

	// destruction of device, window and ImGui.
	void DestroyDevice();
	void DestroyOverlay();
	void DestroyImGui();

	// returns 60.f if it fails.
public:
	void SetupOverlay(const char* window_name) {
		CreateOverlay(window_name);
		CreateDevice();
		CreateImGui();
		ui.Initialize(device, device_context, overlay);
	}

	// deconstructor called when program is exiting. THIS IS CALLED AUTOMATICALLY, NO NEED TO CALL IT YOURSELF!
	~Overlay() {
		DestroyDevice();
		DestroyOverlay();
		DestroyImGui();
	}

	// if we should run the overlay at all
	bool shouldRun = true;

	// for use inside of your main loop to render.
	void StartRender();
	void EndRender();

	// small helper functions for the SetForeground function
	bool IsWindowInForeground(HWND window) { return GetForegroundWindow() == window; }
	bool BringToForeground(HWND window) { return SetForegroundWindow(window); }

	// sets the window to the foreground
	void SetForeground(HWND window);

	// UI access
	UIBase& GetUI() { return ui; }

private:
	// winapi window requirements
	HWND overlay;
	WNDCLASSEX wc;

	ID3D11Device* device;
	ID3D11DeviceContext* device_context;
	IDXGISwapChain* swap_chain;
	ID3D11RenderTargetView* render_targetview;

	UI ui;
};