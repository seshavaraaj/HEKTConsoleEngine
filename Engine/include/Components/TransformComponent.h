#pragma once

struct TransformComponent
{
	float x = 5.0f;
	float y = 5.0f;
	TransformComponent() = default;
	TransformComponent(float x, float y) :
		x(x),
		y(y) {}
};