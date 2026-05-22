#pragma once
#include "Object.h"
#include "Bullet.h"
#include <vector>

class SpaceShip : public IObject
{
public:
	float fireRate = 0.2f;
	float fireRateCounter = 0;

	std::vector<Bullet*> bullets;
	
	SpaceShip();

	void Render() override;

	void Awake() override;

	void Update(float deltaTime) override;

	void Shoot();

	void GenerateBullet();
};