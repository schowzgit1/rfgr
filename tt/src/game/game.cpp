#include "../game/game.h"
#include "../math/math.h"
#include "../window/window.hpp"
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>
#include <iostream>


std::vector<std::string> processes = {
	"FiveM_b2802_GTAProcess.exe",
	"FiveM_b2944_GTAProcess.exe",
	"FiveM_b3095_GTAProcess.exe",
	"FiveM_GTAProcess.exe	",
	"FiveM_b1604_GTAProcess.exe",
	"FiveM_b3274_GTAProcess.exe",
	"FiveM_b3323_GTAProcess.exe",
	"FiveM_b2060_GTAProcess.exe",
	"FiveM_b2189_GTAProcess.exe",
	"FiveM_b2372_GTAProcess.exe",
	"FiveM_b2545_GTAProcess.exe",
	"FiveM_b2612_GTAProcess.exe",
	"FiveM_b2699_GTAProcess.exe"
};

memify mem(processes);

void FiveM::Setup()
{
	auto process_name = mem.GetProcessName();

	using namespace offset;

	auto game_base = mem.GetBase(process_name);
	if (process_name == "FiveM_b1604_GTAProcess.exe") {
		world = mem.Read<uintptr_t>(game_base + 0x247F840);
		replay = mem.Read<uintptr_t>(game_base + 0x1EFD4C8);
		viewport = mem.Read<uintptr_t>(game_base + 0x2087780);
		localplayer = mem.Read<uintptr_t>(world + 0x8);

		playerInfo = 0x10A8;
	}
	if (process_name == "FiveM_b2060_GTAProcess.exe") {
		world = mem.Read<uintptr_t>(game_base + 0x24C8858);
		replay = mem.Read<uintptr_t>(game_base + 0x1EC3828);
		viewport = mem.Read<uintptr_t>(game_base + 0x1F6A7E0);
		localplayer = mem.Read<uintptr_t>(world + 0x8);

		playerInfo = 0x10A8;
	}
	if (process_name == "FiveM_b2189_GTAProcess.exe") {
		world = mem.Read<uintptr_t>(game_base + 0x24E6D90);
		replay = mem.Read<uintptr_t>(game_base + 0x1EE18A8);
		viewport = mem.Read<uintptr_t>(game_base + 0x1F888C0);
		localplayer = mem.Read<uintptr_t>(world + 0x8);

		playerInfo = 0x10A8;
	}
	if (process_name == "FiveM_b2372_GTAProcess.exe") {
		world = mem.Read<uintptr_t>(game_base + 0x252DCD8);
		replay = mem.Read<uintptr_t>(game_base + 0x1F05208);
		viewport = mem.Read<uintptr_t>(game_base + 0x1F9E9F0);
		localplayer = mem.Read<uintptr_t>(world + 0x8);

		playerInfo = 0x10A8;
	}
	if (process_name == "FiveM_b2545_GTAProcess.exe") {
		world = mem.Read<uintptr_t>(game_base + 0x25667E8);
		replay = mem.Read<uintptr_t>(game_base + 0x1F2E7A8);
		viewport = mem.Read<uintptr_t>(game_base + 0x1FD6F70);
		localplayer = mem.Read<uintptr_t>(world + 0x8);

		playerInfo = 0x10A8;
	}
	if (process_name == "FiveM_b2612_GTAProcess.exe") {
		world = mem.Read<uintptr_t>(game_base + 0x2567DB0);
		replay = mem.Read<uintptr_t>(game_base + 0x1F77EF0);
		viewport = mem.Read<uintptr_t>(game_base + 0x1FD8570);
		localplayer = mem.Read<uintptr_t>(world + 0x8);

		playerInfo = 0x10A8;
	}
	if (process_name == "FiveM_b2699_GTAProcess.exe") {
		world = mem.Read<uintptr_t>(game_base + 0x26684D8);
		replay = mem.Read<uintptr_t>(game_base + 0x20304C8);
		viewport = mem.Read<uintptr_t>(game_base + 0x20D8C90);
		localplayer = mem.Read<uintptr_t>(world + 0x8);

		playerInfo = 0x10A8;
	}
	if (process_name == "FiveM_b2802_GTAProcess.exe") {
		world = mem.Read<uintptr_t>(game_base + 0x2593320);
		replay = mem.Read<uintptr_t>(game_base + 0x1F58B58);
		viewport = mem.Read<uintptr_t>(game_base + 0x20019E0);
		localplayer = mem.Read<uintptr_t>(world + 0x8);

		playerInfo = 0x10A8;
	}
	if (process_name == "FiveM_b2944_GTAProcess.exe") {
		world = mem.Read<uintptr_t>(game_base + 0x257BEA0);
		replay = mem.Read<uintptr_t>(game_base + 0x1F42068);
		viewport = mem.Read<uintptr_t>(game_base + 0x1FEAAC0);
		localplayer = mem.Read<uintptr_t>(world + 0x8);

		playerInfo = 0x10A8; // 0x10C8 // 0x10B8
	}
	if (process_name == "FiveM_b3095_GTAProcess.exe") {
		world = mem.Read<uintptr_t>(game_base + 0x25B14B0);
		replay = mem.Read<uintptr_t>(game_base + 0x1FBD4F0);
		viewport = mem.Read<uintptr_t>(game_base + 0x201DBA0);
		localplayer = mem.Read<uintptr_t>(world + 0x8);
		camera = 0x20025B8; // Camera offset for b3095

		playerInfo = 0x10A8;
	}
	if (process_name == "FiveM_GTAProcess.exe") {
		world = mem.Read<uintptr_t>(game_base + 0x25B14B0);
		replay = mem.Read<uintptr_t>(game_base + 0x1FBD4F0);
		viewport = mem.Read<uintptr_t>(game_base + 0x201DBA0);
		localplayer = mem.Read<uintptr_t>(world + 0x8);

		playerInfo = 0x10A8;
	}
	if (process_name == "FiveM_b3274_GTAProcess.exe") {
		world = mem.Read<uintptr_t>(game_base + 0x25B24D8);
		replay = mem.Read<uintptr_t>(game_base + 0x1F76428);
		viewport = mem.Read<uintptr_t>(game_base + 0x201EC20);
		localplayer = mem.Read<uintptr_t>(world + 0x8);

		playerInfo = 0x10A8;
	}
	if (process_name == "FiveM_b3323_GTAProcess.exe") {
		world = mem.Read<uintptr_t>(game_base + 0x25C15B0);
		replay = mem.Read<uintptr_t>(game_base + 0xA1690000);
		viewport = mem.Read<uintptr_t>(game_base + 0x202DC50);
		localplayer = mem.Read<uintptr_t>(world + 0x8);

		playerInfo = 0x10A8;
	}
}

void FiveM::ESP::RunESP(UIBase& ui)
{
	// Only run ESP if enabled in the UI
	if (!ui.IsESPEnabled()) return;

	uintptr_t ped_replay_interface = mem.Read<uintptr_t>(offset::replay + 0x18);
	if (!ped_replay_interface) return;

	uintptr_t pedList = mem.Read<uintptr_t>(ped_replay_interface + 0x100);
	if (!pedList) return;

	auto view_matrix = mem.Read<Matrix>(offset::viewport + 0x24C);

	// Get screen dimensions using GetSystemMetrics
	float screenWidth = static_cast<float>(GetSystemMetrics(SM_CXSCREEN)); // Screen width
	float screenHeight = static_cast<float>(GetSystemMetrics(SM_CYSCREEN)); // Screen height

	// Calculate the bottom middle of the screen
	Vec2 screenBottomMiddle = { screenWidth / 2.0f, screenHeight };

	for (int i = 0; i < 200; i++) {
		uintptr_t ped = mem.Read<uintptr_t>(pedList + (i * 0x10));
		if (!ped || ped == offset::localplayer) continue;

		float health = mem.Read<float>(ped + offset::playerHealth);
		float maxHealth = mem.Read<float>(ped + 0x284);
		if (!health || health > maxHealth) continue;
		Vec3  origin = mem.Read<Vec3>(ped + offset::playerPosition);
		Vec3 rotation = mem.Read<Vec3>(ped + 0x1E0); // Get player rotation

		// Project the player's position to screen space
		Vec2 playerScreenPos;
		if (!origin.world_to_screen(view_matrix, playerScreenPos)) continue;

		// Draw ESP box or other ESP features here
		ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

		// Draw tracer if enabled
		if (ui.IsTracerEnabled()) {
			// Project feet position for tracer
			Vec3 feetPos = origin + Vec3{ 0, 0, -1.0f }; // Offset to feet
			Vec2 feetScreenPos;
			if (feetPos.world_to_screen(view_matrix, feetScreenPos)) {
				draw_list->AddLine(
					ImVec2(screenBottomMiddle.x, screenBottomMiddle.y),
					ImVec2(feetScreenPos.x, feetScreenPos.y),
					ImColor(255, 255, 255, 255),
					1.5f
				);
			}
		}

		// Calculate rotated box corners
		float yaw = rotation.y * (3.14159265f / 180.0f);
		float cosYaw = cos(yaw);
		float sinYaw = sin(yaw);

		Vec3 min = { -0.3f, -0.3f, -1.0f };
		Vec3 max = { 0.3f, 0.3f, 0.9f };

		// Rotate the corners
		Vec3 corners[8];
		corners[0] = origin + Vec3{
			min.x * cosYaw - min.y * sinYaw,
			min.x * sinYaw + min.y * cosYaw,
			min.z
		};
		corners[1] = origin + Vec3{
			max.x * cosYaw - min.y * sinYaw,
			max.x * sinYaw + min.y * cosYaw,
			min.z
		};
		corners[2] = origin + Vec3{
			max.x * cosYaw - max.y * sinYaw,
			max.x * sinYaw + max.y * cosYaw,
			min.z
		};
		corners[3] = origin + Vec3{
			min.x * cosYaw - max.y * sinYaw,
			min.x * sinYaw + max.y * cosYaw,
			min.z
		};
		corners[4] = origin + Vec3{
			min.x * cosYaw - min.y * sinYaw,
			min.x * sinYaw + min.y * cosYaw,
			max.z
		};
		corners[5] = origin + Vec3{
			max.x * cosYaw - min.y * sinYaw,
			max.x * sinYaw + min.y * cosYaw,
			max.z
		};
		corners[6] = origin + Vec3{
			max.x * cosYaw - max.y * sinYaw,
			max.x * sinYaw + max.y * cosYaw,
			max.z
		};
		corners[7] = origin + Vec3{
			min.x * cosYaw - max.y * sinYaw,
			min.x * sinYaw + max.y * cosYaw,
			max.z
		};

		// Project all corners to screen space
		Vec2 screenCorners[8];
		bool allVisible = true;
		for (int i = 0; i < 8; i++) {
			if (!corners[i].world_to_screen(view_matrix, screenCorners[i])) {
				allVisible = false;
				break;
			}
		}

		if (allVisible) {
			// Find bounding box in screen space
			float minX = screenCorners[0].x, maxX = screenCorners[0].x;
			float minY = screenCorners[0].y, maxY = screenCorners[0].y;
			for (int i = 1; i < 8; i++) {
				minX = (std::min)(minX, screenCorners[i].x);
				maxX = (std::max)(maxX, screenCorners[i].x);
				minY = (std::min)(minY, screenCorners[i].y);
				maxY = (std::max)(maxY, screenCorners[i].y);
			}

			float boxWidth = maxX - minX;
			float boxHeight = maxY - minY;
			float boxX = minX;
			float boxY = minY;

			// Draw ESP box
			draw_list->AddRect(
				ImVec2(boxX, boxY),
				ImVec2(boxX + boxWidth, boxY + boxHeight),
				ImColor(255, 255, 255, 255),
				0.0f,
				0,
				1.5f
			);

			// Draw health bar
			float healthBarWidth = 4.0f;
			float healthBarHeight = boxHeight;
			float healthBarX = boxX - healthBarWidth;
			float healthBarY = boxY;
			float healthPercentage = health / maxHealth; // Use maxHealth for percentage

			// Background (red)
			draw_list->AddRectFilled(
				ImVec2(healthBarX, healthBarY),
				ImVec2(healthBarX + healthBarWidth, healthBarY + healthBarHeight),
				ImColor(255, 0, 0, 255)
			);

			// Health (green)
			float healthBarFillHeight = healthBarHeight * healthPercentage;
			draw_list->AddRectFilled(
				ImVec2(healthBarX, healthBarY + healthBarHeight - healthBarFillHeight),
				ImVec2(healthBarX + healthBarWidth, healthBarY + healthBarHeight),
				ImColor(0, 255, 0, 255)
			);

			// Add health text
			char healthText[8];
			sprintf_s(healthText, "%.0f", health);
			float textWidth = ImGui::CalcTextSize(healthText).x;
			float textX = healthBarX - textWidth - 4.0f;
			float textY = healthBarY + healthBarHeight - healthBarFillHeight - 8.0f;
			draw_list->AddText(ImVec2(textX, textY), ImColor(255, 255, 255, 255), healthText);
		}
	}
}

void FiveM::ESP::RunTracer(UIBase& ui)
{
	// Only run tracer if enabled in the UI
	if (!ui.IsTracerEnabled()) return;

	uintptr_t ped_replay_interface = mem.Read<uintptr_t>(offset::replay + 0x18);
	if (!ped_replay_interface) return;

	uintptr_t pedList = mem.Read<uintptr_t>(ped_replay_interface + 0x100);
	if (!ped_replay_interface) return;

	auto view_matrix = mem.Read<Matrix>(offset::viewport + 0x24C);

	// Get screen dimensions using GetSystemMetrics
	float screenWidth = static_cast<float>(GetSystemMetrics(SM_CXSCREEN)); // Screen width
	float screenHeight = static_cast<float>(GetSystemMetrics(SM_CYSCREEN)); // Screen height

	// Calculate the bottom middle of the screen
	Vec2 screenBottomMiddle = { screenWidth / 2.0f, screenHeight };

	for (int i = 0; i < 200; i++) {
		uintptr_t ped = mem.Read<uintptr_t>(pedList + (i * 0x10));
		if (!ped || ped == offset::localplayer) continue;

		float health = mem.Read<float>(ped + offset::playerHealth);
		float maxHealth = mem.Read<float>(ped + 0x284);
		if (!health || health > maxHealth) continue;

		Vec3 origin = mem.Read<Vec3>(ped + offset::playerPosition);

		// Project feet position for tracer
		Vec3 feetPos = origin + Vec3{ 0, 0, -1.0f }; // Offset to feet
		Vec2 feetScreenPos;
		if (!feetPos.world_to_screen(view_matrix, feetScreenPos)) continue;

		// Draw the tracer line to feet
		ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
		draw_list->AddLine(
			ImVec2(screenBottomMiddle.x, screenBottomMiddle.y),
			ImVec2(feetScreenPos.x, feetScreenPos.y),
			ImColor(255, 255, 255, 255),
			1.5f
		);
	}
}


