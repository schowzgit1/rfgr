#include "game.h"
#include "../math/math.h"
#include "../window/window.hpp"
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
	uintptr_t ped_replay_interface = mem.Read<uintptr_t>(offset::replay + 0x18);
	if (!ped_replay_interface)
		return;

	uintptr_t pedlist = mem.Read<uintptr_t>(ped_replay_interface + 0x100);
	if (!pedlist)
		return;
	
	auto view_matrix = mem.Read<Matrix>(offset::viewport + 0x24C);

	for (int i = 0; i < 200; i++) {
		uintptr_t ped = mem.Read<uintptr_t>(pedlist + (i * 0x10));
		if (!ped)
			continue;

		if (ped == offset::localplayer)
			continue;

		float health = mem.Read<float>(ped + offset::playerHealth);
		if (!health)
			continue; 
		Vec3  origin = mem.Read<Vec3>(ped + offset::playerPosition);
		
		Vec2 org;
		if (origin.world_to_screen(view_matrix, org)) {
			ImDrawList* draw_list;

			draw_list->AddCircle({ org.x, org.y }, 1.5, ImColor(255, 255, 255));

		}
	}
}
