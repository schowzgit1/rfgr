#include "game.h"
#include "../math/math.h"
#include "../window/window.hpp"
#include <iostream>

std::vector<std::string> processes = {  
	"FiveM_b2802_GTAProcess.exe",
	"FiveM_b2944_GTAProcess.exe",
	"FiveM_b3095_GTAProcess.exe"
};

memify mem(processes);  

void FiveM::Setup()
{
	auto process_name = mem.GetProcessName();

	using namespace offset;

	auto game_base = mem.GetBase(process_name);
	if (process_name == "FiveM_b3095_GTAProcess.exe") {
		world = mem.Read<uintptr_t>(game_base + 0x2593320); // 0x254d448
		replay = mem.Read<uintptr_t>(game_base + 0x1F58B58); // 0X1F5B820
		viewport = mem.Read<uintptr_t>(game_base + 0x20019E0); // 0x1FBC100
		localplayer = mem.Read<uintptr_t>(world + 0x8);

		playerInfo = 0x10A8;
	}
	if (process_name == "FiveM_b2944_GTAProcess.exe") {
		world = mem.Read<uintptr_t>(game_base + 0x257BEA0);
		replay = mem.Read<uintptr_t>(game_base + 0x1F42068);
		viewport = mem.Read<uintptr_t>(game_base + 0x1FEAAC0);
		localplayer = mem.Read<uintptr_t>(world + 0x8);

		playerInfo = 0x10A8; // 0x10C8
	}
	if (process_name == "FiveM_b2802_GTAProcess.exe") {
		world = mem.Read<uintptr_t>(game_base + 0x2593320);
		replay = mem.Read<uintptr_t>(game_base + 0x1F58B58);
		viewport = mem.Read<uintptr_t>(game_base + 0x20019E0);
		localplayer = mem.Read<uintptr_t>(world + 0x8);

		playerInfo = 0x10A8;
	}
}

void FiveM::ESP::RunESP()
{
    std::cout << "[DEBUG] ESP Running..." << std::endl;

    uintptr_t ped_replay_interface = mem.Read<uintptr_t>(offset::replay + 0x18);
    if (!ped_replay_interface) {
        std::cout << "[ERROR] Invalid ped_replay_interface!" << std::endl;
        return;
    }

    uintptr_t pedlist = mem.Read<uintptr_t>(ped_replay_interface + 0x100);
    if (!pedlist) {
        std::cout << "[ERROR] Invalid pedlist!" << std::endl;
        return;
    }

    auto view_matrix = mem.Read<Matrix>(offset::viewport + 0x24C);

    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
    if (!draw_list) {
        std::cout << "[ERROR] ImGui Draw List Not Found!" << std::endl;
        return;
    }

    for (int i = 0; i < 200; i++) {
        uintptr_t ped = mem.Read<uintptr_t>(pedlist + (i * 0x10));
        if (!ped) continue;

        std::cout << "[DEBUG] Processing Ped " << i << std::endl;

        float health = mem.Read<float>(ped + offset::playerHealth);
        if (health <= 0) {
            std::cout << "[DEBUG] Skipping Ped " << i << " - Health: " << health << std::endl;
            continue;
        }

        Vec3 origin = mem.Read<Vec3>(ped + offset::playerPosition);
        Vec2 screen_pos;
        if (!origin.world_to_screen(view_matrix, screen_pos)) {
            std::cout << "[ERROR] W2S Failed for Ped " << i << std::endl;
            continue;
        }

        std::cout << "[DEBUG] Drawing ESP for Ped " << i << " at (" << screen_pos.x << ", " << screen_pos.y << ")" << std::endl;
        draw_list->AddCircle({ screen_pos.x, screen_pos.y }, 1.5, ImColor(255, 255, 255));
    }
}

