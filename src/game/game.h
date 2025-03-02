#pragma once
#include <cstdint>
#include "../mem/memify.h"

std::vector<std::string> processes = {
	"FiveM_b2802_GTAProcess.exe"
	"FiveM_b2944_GTAProcess.exe"
	"FiveM_b3095_GTAProcess.exe"
};
memify mem(processes);

namespace FiveM {
	namespace offset {
		uintptr_t world, replay, viewport, localplayer;
		uintptr_t boneList, boneMatrix = 0x60;
		uintptr_t playerInfo, playerHealth = 0x280, playerPosition = 0x90;
		uintptr_t base;
}
	namespace ESP {
		void RunESP();
	}
	void Setup();
}	 