#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <iostream>
#include <Components.h>


namespace HEKTConsoleEngine
{
	class SpriteParser
	{
	private:
		std::string BuildFilePath(const std::string& filePath);
	public:
		const std::wstring ParseSprite(const std::string& filePath);
		const SpriteComponent ParseSpriteComponent(const std::string& filePath, WORD color);
	};
}