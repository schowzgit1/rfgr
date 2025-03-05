#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include "../mem/memify.h"

extern std::vector<std::string> processes;  
extern memify mem;  

namespace FiveM {
    namespace offset {
        inline uintptr_t world, replay, viewport, localplayer;
        inline uintptr_t boneList, boneMatrix = 0x60;
        inline uintptr_t playerInfo, playerHealth = 0x280, playerPosition = 0x90;
        inline uintptr_t base;
    }
    namespace ESP {
        void RunESP();
    }
    void Setup();
}