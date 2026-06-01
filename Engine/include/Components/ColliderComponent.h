#pragma once
#include <entt/entt.hpp>

struct ColliderComponent
{
	bool isTrigger = false;
	int height;
	int width;
	int offsetX;
	int offsetY;
	ColliderComponent() = default;
	ColliderComponent(int height = 0, int width = 0, bool istrigger = false) : 
		height(height), 
		width(width),
		isTrigger(istrigger),
		offsetX(0), 
		offsetY(0) {}
	ColliderComponent(int height, int width, int offsetX, int offsetY, bool isTrigger = false) : 
		height(height), 
		width(width), 
		offsetX(offsetX), 
		offsetY(offsetY),
		isTrigger(isTrigger){}
};

struct CollisionInfo
{
	entt::entity checkingEntity;
	entt::entity collidingEntity;
};