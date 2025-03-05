#include "window/window.hpp"
#include "game/game.h"
#include <thread>
#include <iostream>

int main() {
	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	Overlay overlay;
	
	overlay.SetupOverlay("gra");

	FiveM::Setup();

	std::vector<std::string> processes = { "1", "2", "3" };
	for (auto& process : processes) {
		std::cout << process;
	}

	while (overlay.shouldRun) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		overlay.StartRender(); 

		UI& ui = overlay.GetUI();
		FiveM::ESP::RunESP(ui);
		FiveM::ESP::RunTracer(ui);

		// The menu is now rendered through the UI system
		overlay.EndRender();
	}
}
