#include "Screen.h"
#include "Input.h"
#include "Main.h"
#include "SpaceShip.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Score.h"
#include <chrono>
#include <string>
#include <thread>

const int TARGET_FRAME_RATE = 60;
const bool FRAME_RATE_CAP = false;
const bool RENDER_COLOR_BUFFER = true;

std::vector<IObject*> IObjects;

std::chrono::duration<float> deltaTime;
std::chrono::duration<float> targetFrameTime = std::chrono::duration<float>(1.0f / TARGET_FRAME_RATE);
float fDeltaTime;
bool debugMode = false;

int score = 0;

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
		SetObjectCollisionUpdates();
		SetObjectUpdates(fDeltaTime);
		SetObjectRenders();
		HandleDebug();
		HandleQuit();
		RenderScreenBuffer();
		if (RENDER_COLOR_BUFFER) RenderColorBuffer();
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
	WORD textColor = LightGreen;
	std::string debugString =
		"Delta Time: " + std::to_string(fDeltaTime) +
		" FPS: " + std::to_string(1 / fDeltaTime) +
		" Objects: " + std::to_string((int)IObjects.size());
	size_t length = debugString.copy(screenBuffer, 209);
	for (size_t i = 0; i < length; i++) {
		colorBuffer[i] = textColor;
	}
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

void SetObjectCollisionUpdates()
{
	for (int i = (int)IObjects.size() - 1; i >= 0; i--)
	{
		IObjects[i]->previousCollidingObjects = IObjects[i]->collidingObjects;
		IObjects[i]->collidingObjects.clear();
		for (int j = (int)IObjects.size() - 1; j >= 0; j--)
		{
			if (i != j)
			{
				IObjects[i]->CheckCollision(IObjects[j]);
			}
		}
	}
}

void ObjectInitialization()
{
	SpaceShip* spaceShip = new SpaceShip({ 10, 50 });
	Enemy* enemy1 = new Enemy({ 10, 10 });
	Enemy* enemy2 = new Enemy({ 209, 15 });
	enemy2->direction = -1;
	Score* score = new Score({ 180, 2 });
}