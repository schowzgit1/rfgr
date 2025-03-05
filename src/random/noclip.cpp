#include "noclip.h"
#include "../game/game.h"
#include "../math/math.h"
#include <cmath>

void FiveM::ESP::Noclip()
{
    uintptr_t localPlayer = FiveM::offset::localplayer;

    if (localPlayer) {
        Vec3 playerPosition = mem.Read<Vec3>(localPlayer + 0x90);
        static float noclipspeed = 50;
        uintptr_t camera = mem.Read<uintptr_t>(FiveM::offset::base + FiveM::offset::camera + 0x0);
        Vec3 cameraAngles = mem.Read<Vec3>(camera + 0x03D0);

        uintptr_t physics = mem.Read<uintptr_t>(localPlayer + 0x30);
        if (physics) {
            mem.Write<float>(physics + 0x00D0, 0.0f);
        }


        float pitch = cameraAngles.x * (3.14159265f / 180.0f);
        float yaw = cameraAngles.y * (3.14159265f / 180.0f);

        Vec3 forward = {
            cos(pitch) * sin(yaw),
            cos(pitch) * cos(yaw),
            sin(pitch)
        };

        Vec3 right = {
            -cos(yaw),
            sin(yaw),
            0
        };

        Vec3 up = { 0, 0, 1 };


        if (GetAsyncKeyState(VK_UP) & 0x8000)
        {
            playerPosition.x += forward.x * noclipspeed;
            playerPosition.y += forward.y * noclipspeed;
            playerPosition.z += forward.z * noclipspeed;
        }

        if (GetAsyncKeyState(VK_DOWN) & 0x8000)
        {
            playerPosition.x -= forward.x * noclipspeed;
            playerPosition.y -= forward.y * noclipspeed;
            playerPosition.z -= forward.z * noclipspeed;
        }

        if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            playerPosition.x += right.x * noclipspeed;
            playerPosition.y += right.y * noclipspeed;
        }

        if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            playerPosition.x -= right.x * noclipspeed;
            playerPosition.y -= right.y * noclipspeed;
        }

        if (GetAsyncKeyState(0x45) & 0x8000)
        {
            playerPosition.z += noclipspeed;
        }

        if (GetAsyncKeyState(0x51) & 0x8000)
        {
            playerPosition.z -= noclipspeed;
        }

        float lookSpeed = 2.0f;
        if (GetAsyncKeyState(0x41) & 0x8000)
        {
            cameraAngles.y -= lookSpeed;
        }

        if (GetAsyncKeyState(0x44) & 0x8000)
        {
            cameraAngles.y += lookSpeed;
        }

        mem.Write<Vec3>(camera + 0x03D0, cameraAngles);

        mem.Write<Vec3>(localPlayer + 0x1E0, cameraAngles);

        mem.Write<Vec3>(localPlayer + 0x90, playerPosition);

        uintptr_t navigation = mem.Read<uintptr_t>(localPlayer + 0x30);
        if (navigation) {
            mem.Write<Vec3>(navigation + 0x30, playerPosition);
            mem.Write<Vec3>(navigation + 0x50, playerPosition);
        }
    }
}