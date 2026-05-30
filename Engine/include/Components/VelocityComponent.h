#pragma once
struct VelocityComponent
{
	float dx = 0.0f;
	float dy = 0.0f;
	VelocityComponent() = default;
	VelocityComponent(float x, float y) :
		dx(x),
		dy(y) {}
};