#pragma once
#include <entt/entt.hpp>
#include <Windows.h>
#include <Renderer.h>
#include <RenderSystem.h>
#include <InputSystem.h>
#include <EntityManager.h>
#include <PhysicsSystem.h>
#include <chrono>
#include <thread>

namespace HEKTConsoleEngine {
    class Application {
    public:
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

    private:
		Renderer renderer;
		RenderSystem renderSystem{ registry, renderer };
		PhysicsSystem physicsSystem{ registry };
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
        void HandleDebug(Renderer& render);
		void HandleTPSCap();
		void HandleQuit();
    };
}