#include "Input.h"
#include <windows.h>

bool currentKeyState[256] = { false };
bool previousKeyState[256] = { false };

int UsingKeys[] = { VK_LEFT, VK_RIGHT, VK_SPACE, VK_ACCEPT, VK_ESCAPE , VK_F3};
int UsingKeysCount = sizeof(UsingKeys) / sizeof(UsingKeys[0]);

void UpdateKeyStates()
{
	for (int key : UsingKeys)
	{
		previousKeyState[key] = currentKeyState[key];
		currentKeyState[key] = GetAsyncKeyState(key) & 0x8000;
	}
}

bool GetKeyDown(int key)
{
	return currentKeyState[key] && !previousKeyState[key];
}

bool GetKeyUp(int key)
{
	return !currentKeyState[key] && previousKeyState[key];
}

bool GetKey(int key)
{
	return currentKeyState[key];
}