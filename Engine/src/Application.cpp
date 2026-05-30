#include "Application.h"
#include <Renderer.h>
#include <iostream>

namespace HEKTConsoleEngine {
    void Application::Run() 
    {
		Renderer renderer;
        while (true)
        {
			timePoint2 = std::chrono::high_resolution_clock::now();
			deltaTime = timePoint2 - timePoint1;
			timePoint1 = timePoint2;
			fDeltaTime = deltaTime.count();
			renderer.HandleResize();
			renderer.ClearScreenBuffer();
			LogicUpdate();
            HandleDebug(renderer);
			renderer.RenderScreenBuffer();
			HandleTPSCap();
        }
    }

    Application::Application() 
    {
        SetFullscreen();
		LockHideCursor();
    }

    void Application::LogicUpdate() 
    {
	}

    void Application::SetFullscreen() 
    {
        keybd_event(VK_F11, 0, 0, 0);
        keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);
	}

    void Application::LockHideCursor() 
    {
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hOut, &cursorInfo);
        cursorInfo.bVisible = FALSE;
		SetConsoleCursorInfo(hOut, &cursorInfo);
	}

    void Application::HandleDebug(Renderer& render) 
    {
		render.CopyToScreenBuffer("|DeltaTime: " + std::to_string(fDeltaTime) +
                                  "|TPS: " + std::to_string(1 / fDeltaTime));
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
}