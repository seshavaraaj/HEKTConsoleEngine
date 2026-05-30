#include "Application.h"
#include <iostream>

namespace HEKTConsoleEngine {
    void Application::Run() 
    {
		AppStart();
        while (isRunning)
        {
			timePoint2 = std::chrono::high_resolution_clock::now();
			deltaTime = timePoint2 - timePoint1;
			timePoint1 = timePoint2;
			fDeltaTime = deltaTime.count();
			inputSystem.UpdateKeyStates();
			renderer.HandleResize();
			renderer.ClearScreenBuffer();
			physicsSystem.Update(fDeltaTime);
			renderSystem.Update();
			AppUpdate();
            HandleDebug(renderer);
			renderer.RenderScreenBuffer();
			renderer.RenderColorBuffer();
            HandleTPSCap();
            HandleQuit();
        }
    }

    void Application::QuitOn(int key)
    {
		QuittingKey = key;
    }

    void Application::DebugOn(int key)
    {
		DebugKey = key;
    }

    Application::Application() 
    {
        SetFullscreen();
    }

    void Application::AppUpdate() 
    {
        if (OnUpdate)
        {
			OnUpdate(fDeltaTime);
        }
	}

    void Application::AppStart() 
    {
        if (OnStart)
        {
            OnStart();
        }
	}

    void Application::SetFullscreen() 
    {
        keybd_event(VK_F11, 0, 0, 0);
        keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);
	}

    void Application::HandleDebug(Renderer& render) 
    {
        if (DebugKey == NULL) return;
        if (inputSystem.GetKeyDown(DebugKey))
        {
			debugMode = !debugMode;
        }
		if (!debugMode) return;
		size_t entityCount = registry.storage<entt::entity>().capacity();

        std::string debugInfo = 
            "|DeltaTime: " + std::to_string(fDeltaTime) +
            "|TPS: " + std::to_string(1 / fDeltaTime) +
			"\n|Entities: " + std::to_string(entityCount);
        for (auto&& [id, pool] : registry.storage())
        {
            std::string_view componentName = pool.info().name();

            size_t count = pool.size(); 

            debugInfo += "\n[";
            debugInfo += componentName;
            debugInfo += ": " + std::to_string(count);
			debugInfo += "]";
        }

		render.SetBufferString(0, 0, debugInfo, Color::LightGreen);
	}

    void Application::HandleTPSCap()
    {
		if (targetTPS <= 0) return;
		auto targetWakeTime = timePoint2 + targetFrameTime;
		std::this_thread::sleep_until(targetWakeTime);
    }

    void Application::SetTargetTPS(int tps)
    {
		targetTPS = tps;
		targetFrameTime = std::chrono::duration<float>(1.0f / targetTPS);
    }

    entt::registry& Application::GetRegistry()
    {
        return registry;
    }

    void Application::HandleQuit()
    {
        if (QuittingKey != NULL && inputSystem.GetKeyDown(QuittingKey))
        {
			isRunning = false;
        }
    }
}