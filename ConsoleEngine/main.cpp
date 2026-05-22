#include "Screen.h"
#include "Input.h"
#include "Main.h"
#include "SpaceShip.h"
#include "Bullet.h"
#include <chrono>
#include <string>
#include <thread>

const int TARGET_FRAME_RATE = 60;
const bool FRAME_RATE_CAP = false;

std::vector<IObject*> IObjects;

std::chrono::duration<float> deltaTime;
std::chrono::duration<float> targetFrameTime = std::chrono::duration<float>(1.0f / TARGET_FRAME_RATE);
float fDeltaTime;
bool debugMode = false;

int main()
{
	auto timePoint1 = std::chrono::high_resolution_clock::now();
	auto timePoint2 = std::chrono::high_resolution_clock::now();

	LockHideCursor();
	SetFullscreen();
	SetupCustomBuffer();
	SetObjectAwakes();
	ObjectInitialization();

	while (true)
	{
		timePoint2 = std::chrono::high_resolution_clock::now();
		deltaTime = timePoint2 - timePoint1;
		timePoint1 = timePoint2;
		fDeltaTime = deltaTime.count();

		ClearScreenBuffer();
		SetObjectUpdates(fDeltaTime);
		SetObjectRenders();
		HandleDebug();
		HandleQuit();
		RenderScreenBuffer();
		UpdateKeyStates();
		
		if (FRAME_RATE_CAP)
		{
			auto targetWakeTime = timePoint2 + targetFrameTime;
			std::this_thread::sleep_until(targetWakeTime);
		}
	}
	return 0;
}

void Debug()
{
	std::string debugString = "Delta Time: " + std::to_string(fDeltaTime) + " FPS: " + std::to_string(1/fDeltaTime);
	debugString.copy(screenBuffer, 209);
}

void HandleDebug()
{
	if (GetKeyDown(VK_F3))
	{
		debugMode = !debugMode;
	}
	if (debugMode) Debug();
}

void HandleQuit()
{
	if (GetKeyDown(VK_ESCAPE))
	{
		exit(0);
	}
}

void SetObjectRenders()
{
	for (int i = (int)IObjects.size() - 1; i >= 0; i--)
	{
		IObjects[i]->Render();
	}
}

void SetObjectUpdates(float deltaTime)
{
	for (int i = (int)IObjects.size() - 1; i >= 0; i--)
	{
		IObjects[i]->Update(deltaTime);
	}
}

void SetObjectAwakes()
{
	for (int i = (int)IObjects.size() - 1; i >= 0; i--)
	{
		IObjects[i]->Awake();
	}
}

void ObjectInitialization()
{
	SpaceShip* spaceShip = new SpaceShip();
}