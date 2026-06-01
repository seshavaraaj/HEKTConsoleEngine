#pragma once
#include <Windows.h>
#include <string>

struct SpriteComponent
{
	int width = 0;
	int height = 0;
	std::wstring spriteData;
	WORD* colorData = nullptr;
	WORD color = 0x000F;
	SpriteComponent() = default;
	SpriteComponent(int width, int height, const std::wstring& spriteData, WORD color) :
		width(width),
		height(height),
		spriteData(spriteData),
		color(color) {}
};