#include "../game/game.h"
#include "../math/math.h"
#include "../window/window.hpp"

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
        world = mem.Read<uintptr_t>(game_base + 0x25B14B0); // 0x254d448
        replay = mem.Read<uintptr_t>(game_base + 0x1FBD4F0); // 0X1F5B820
        viewport = mem.Read<uintptr_t>(game_base + 0x201DBA0); // 0x1FBC100
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

    uintptr_t pedList = mem.Read<uintptr_t>(ped_replay_interface + 0x100);
    if (!ped_replay_interface)
        return;

    auto view_matrix = mem.Read<Matrix>(offset::viewport + 0x24C);

    for (int i = 0; i < 200; i++)
    {
        uintptr_t ped = mem.Read<uintptr_t>(pedList + (i * 0x10));
        if (!ped)
            continue;

        if (ped == offset::localplayer)
            continue;

        auto playerInfo = mem.Read<uintptr_t>(ped + offset::playerInfo);

        auto bonelist = mem.Read<uintptr_t>(ped + 0x410);
        auto bonematrix = mem.Read<Matrix>(ped + offset::boneMatrix);

        float health = mem.Read<float>(ped + offset::playerHealth);
        if (!health)
            continue;

        Vec3 origin = mem.Read<Vec3>(ped + offset::playerPosition);

        // Define the bounding box dimensions (adjust these values as needed)
        Vec3 min = { -0.3f, -0.3f, -1.0f }; // Lower bounds (bottom half remains the same)
        Vec3 max = { 0.3f, 0.3f, 0.9f };    // Upper bounds (increase max.z to make the top half taller)

        // Calculate the 8 corners of the bounding box
        Vec3 corners[8] = {
            { min.x, min.y, min.z },
            { min.x, min.y, max.z },
            { min.x, max.y, min.z },
            { min.x, max.y, max.z },
            { max.x, min.y, min.z },
            { max.x, min.y, max.z },
            { max.x, max.y, min.z },
            { max.x, max.y, max.z }
        };

        // Transform the corners to world space
        for (int j = 0; j < 8; j++) {
            corners[j] = origin + corners[j];
        }

        // Project the corners to screen space
        Vec2 screenCorners[8];
        bool allCornersVisible = true;
        for (int j = 0; j < 8; j++) {
            if (!corners[j].world_to_screen(view_matrix, screenCorners[j])) {
                allCornersVisible = false;
                break;
            }
        }

        if (allCornersVisible) {
            // Find the min and max screen coordinates to draw the box
            Vec2 minScreen = screenCorners[0];
            Vec2 maxScreen = screenCorners[0];
            for (int j = 1; j < 8; j++) {
                minScreen.x = min(minScreen.x, screenCorners[j].x);
                minScreen.y = min(minScreen.y, screenCorners[j].y);
                maxScreen.x = max(maxScreen.x, screenCorners[j].x);
                maxScreen.y = max(maxScreen.y, screenCorners[j].y);
            }

            // Draw the box
            ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
            draw_list->AddRect({ minScreen.x, minScreen.y }, { maxScreen.x, maxScreen.y }, ImColor(255, 255, 255, 255));
        }
    }

}


