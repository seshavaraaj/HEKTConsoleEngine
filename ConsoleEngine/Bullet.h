#include "Object.h"
#pragma once

enum Direction
{
	Up,
	Down,
	Left,
	Right
};

class Bullet : public IObject
{
public:
	int speed = 80;
	Direction direction = Up;
	Bullet(Transform transform);
	void Render() override;
	void Awake() override;
	void Update(float deltaTime) override;
	void Move(float deltaTime);
};