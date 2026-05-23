#pragma once
#include "Object.h"
#include "Bullet.h"
#include <vector>

class Enemy : public IObject
{
public:
	int health = 100;
	int speed = 20;
	int shootInterval = 1;
	int direction = 1;
	float shootIntervalCounter = 0;
	std::vector<Bullet*> bullets;
	Enemy(Transform transform);
	~Enemy();
	void Render() override;
	void Awake() override;
	void Update(float deltaTime) override;
	void Shoot();
	void GenerateBullet();
	void Strafe(float deltaTime);
};

