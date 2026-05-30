#pragma once
#include <string>

struct SpriteComponent
{
	int width = 0;
	int height = 0;
	std::string spriteData;
	SpriteComponent() = default;
	SpriteComponent(int width, int height, const std::string& spriteData) :
		width(width),
		height(height),
		spriteData(spriteData) {}
	SpriteComponent(int width, int height, const std::string& spriteData, int offsetX, int offsetY) :
		width(width),
		height(height),
		spriteData(spriteData) {}
};