#include "InputSystem.h"

namespace HEKTConsoleEngine
{
	void InputSystem::SetUsingKeys(const std::vector<int>& keys)
	{
		usingKeys = keys;
	}

	void InputSystem::UpdateKeyStates()
	{
		if (usingKeys.empty())
		{
			for (int i = 0; i < 256; i++)
			{
				previousKeyStates[i] = currentKeyStates[i];
				currentKeyStates[i] = (GetAsyncKeyState(i) & 0x8000) != 0;
			}
			return;
		}

		for (int key : usingKeys)
		{
			previousKeyStates[key] = currentKeyStates[key];
			currentKeyStates[key] = (GetAsyncKeyState(key) & 0x8000) != 0;
		}
	}
	bool InputSystem::GetKeyDown(int key)
	{
		return currentKeyStates[key] && !previousKeyStates[key];
	}
	bool InputSystem::GetKeyUp(int key)
	{
		return !currentKeyStates[key] && previousKeyStates[key];
	}
	bool InputSystem::GetKey(int key)
	{
		return currentKeyStates[key];
	}
}