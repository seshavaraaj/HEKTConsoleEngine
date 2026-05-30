#pragma once
#include <Windows.h>
#include <vector>

namespace HEKTConsoleEngine
{
	class InputSystem
	{
	private:
		bool currentKeyStates[256] = { false };
		bool previousKeyStates[256] = { false };
		std::vector<int> usingKeys;

	public:
		void SetUsingKeys(const std::vector<int>& keys);
		void UpdateKeyStates();
		bool GetKeyDown(int key);
		bool GetKeyUp(int key);
		bool GetKey(int key);
	};
}