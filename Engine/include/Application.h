#pragma once
#include <entt/entt.hpp>
#include <Windows.h>
#include <Renderer.h>
#include <chrono>
#include <thread>

namespace HEKTConsoleEngine {
    class Application {
    public:
        void Run();
        Application();
        void SetTargetTPS(int tps);

    private:
		int targetTPS = 0;
		entt::registry registry;
		float fDeltaTime;
		std::chrono::duration<float> targetFrameTime = std::chrono::duration<float>(1.0f / targetTPS);
		std::chrono::duration<float> deltaTime;
		std::chrono::high_resolution_clock::time_point timePoint1 = std::chrono::high_resolution_clock::now();
		std::chrono::high_resolution_clock::time_point timePoint2 = std::chrono::high_resolution_clock::now();
        void LogicUpdate();
		void SetFullscreen();
        void LockHideCursor();
        void HandleDebug(Renderer& render);
		void HandleTPSCap();
    };
}