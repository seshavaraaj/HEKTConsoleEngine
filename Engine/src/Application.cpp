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
            renderer.ClearFullScreenBuffer();

			physicsSystem.Update(fDeltaTime);
			renderSystem.Update();

			AppUpdate();
            HandleDebug();

			renderer.RenderDirtyRectBuffer();
            //renderer.RenderFullScreenBuffer();
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
#ifdef _DEBUG
		DebugKey = key;
#endif // DEBUG
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
		Sleep(100);
        keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);
	}

    void Application::HandleDebug() 
    {
        if (DebugKey == NULL) return;
        if (inputSystem.GetKeyDown(DebugKey))
        {
			debugMode = !debugMode;
        }
        if (!debugMode) return;

        std::wstring debugInfo;

		debugInfo += L"Debug Mode ON\n";
		debugInfo += L"DeltaTime: " + std::to_wstring(fDeltaTime) + L"\n";
		debugInfo += L"TPS: " + std::to_wstring(1.0f / fDeltaTime) + L"\n";
		debugInfo += L"Dirty Rect: " + std::to_wstring(renderer.GetDirtyRectPrevious().Top) + L"," + std::to_wstring(renderer.GetDirtyRectPrevious().Left) + L"," + std::to_wstring(renderer.GetDirtyRectPrevious().Bottom) + L"," + std::to_wstring(renderer.GetDirtyRectPrevious().Right) + L"\n";
		debugInfo += L"Entities: " + std::to_wstring(registry.storage<entt::entity>().size()) + L"\n";

        renderer.SetBufferString(0, 0, debugInfo, Color::LightGreen);
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