#pragma once
#include "Object.h"
#include "Bullet.h"
#include <vector>

class SpaceShip : public IObject
{
public:
	float fireRate = 0.2f;
	float fireRateCounter = 0;
	int health = 100;

	std::vector<Bullet*> bullets;
	
	SpaceShip(Transform transform);

	void Render() override;

	void Awake() override;

	void Update(float deltaTime) override;

	void Shoot();

	void GenerateBullet();
};