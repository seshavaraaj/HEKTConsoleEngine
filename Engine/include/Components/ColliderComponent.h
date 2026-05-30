#pragma once

struct ColliderComponent
{
	int height;
	int width;
	int offsetX;
	int offsetY;
	ColliderComponent() = default;
	ColliderComponent(int height = 0, int width = 0) : 
		height(height), 
		width(width), 
		offsetX(0), 
		offsetY(0) {}
	ColliderComponent(int height, int width, int offsetX, int offsetY) : 
		height(height), 
		width(width), 
		offsetX(offsetX), 
		offsetY(offsetY) {}
};