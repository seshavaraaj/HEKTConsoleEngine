#pragma once
#include <entt/entt.hpp>
#include <Windows.h>
#include <Renderer.h>
#include <RenderSystem.h>
#include <InputSystem.h>
#include <EntityManager.h>
#include <PhysicsSystem.h>
#include <SpriteParser.h>
#include <chrono>
#include <thread>

namespace HEKTConsoleEngine {
    class Application {
    public:
		void SetRenderType(RenderType type);
		void DebugOn(int key);
		void QuitOn(int key);
        void Run();
        Application();
        void SetTargetTPS(int tps);
		entt::registry& GetRegistry();
		InputSystem inputSystem;

		std::function<void(float)> OnUpdate = nullptr;
		std::function<void()> OnStart = nullptr;
		EntityManager entityManager{ registry };
		SpriteParser spriteParser;
		PhysicsSystem physicsSystem{ registry };

    private:
		Renderer renderer;
		RenderSystem renderSystem{ registry, renderer };
		float fDeltaTime;
		bool isRunning = true;
		bool debugMode = false;
		int targetTPS = 0;
		int QuittingKey = NULL;
		int DebugKey = NULL;
		entt::registry registry;
		std::chrono::duration<float> targetFrameTime = std::chrono::duration<float>(1.0f / targetTPS);
		std::chrono::duration<float> deltaTime;
		std::chrono::high_resolution_clock::time_point timePoint1 = std::chrono::high_resolution_clock::now();
		std::chrono::high_resolution_clock::time_point timePoint2 = std::chrono::high_resolution_clock::now();
        void AppUpdate();
		void AppStart();
		void SetFullscreen();
        void HandleDebug();
		void HandleTPSCap();
		void HandleQuit();
		void RenderSplashScreen();

		const wchar_t* ENGINE_SPLASH_SCREEN = LR"(
    ===================================================
     _    _ ______ _  _ _______  _____             _ 
    | |  | |  ____| |/ /__   __|/ ____|           | |
    | |__| | |__  | ' /   | |  | |     ___  _ __  | |
    |  __  |  __| |  <    | |  | |    / _ \| '_ \ | |
    | |  | | |____| . \   | |  | |___| (_) | | | ||_|
    |_|  |_|______|_|\_\  |_|   \_____\___/|_| |_|(_)
                                                     
                     CONSOLE ENGINE v1.0
    ===================================================
    )";
    };
}