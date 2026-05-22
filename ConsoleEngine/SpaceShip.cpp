#include "SpaceShip.h"
#include "Object.h"
#include "Screen.h"
#include "input.h"
#include "Bullet.h"
#include <vector>

SpaceShip::SpaceShip() : IObject(Transform{}, Sprite{})
{
	transform.positionX = 100;
	transform.positionY = 50;
}

void SpaceShip::Render()
{
	SetBufferChar(GetTransformX() + 1, GetTransformY(), '\xDB');
	SetBufferChar(GetTransformX(), GetTransformY(), '\xDB');
	SetBufferChar(GetTransformX() - 1, GetTransformY(), '\xDB');

	SetBufferChar(GetTransformX() - 2, GetTransformY(), '\xDC');
	SetBufferChar(GetTransformX() + 2, GetTransformY(), '\xDC');

	SetBufferChar(GetTransformX(), GetTransformY() - 1, '\xDC');
}

void SpaceShip::Shoot()
{
	GenerateBullet();
}

void SpaceShip::Awake()
{
}

void SpaceShip::Update(float deltaTime)
{
	if (GetKey(VK_LEFT))
	{
		transform.positionX -= 50 * deltaTime;
	}
	if (GetKey(VK_RIGHT))
	{
		transform.positionX += 50 * deltaTime;
	}
	if (GetKey(VK_SPACE))
	{
		if (fireRateCounter <= 0)
		{
			fireRateCounter = fireRate;
			Shoot();
		}
	}

	if (fireRateCounter > 0)
	{
		fireRateCounter -= deltaTime;
	}
}

void SpaceShip::GenerateBullet()
{
	Bullet* bullet = new Bullet(Transform{ transform.positionX, transform.positionY - 1 }, Sprite{});
	bullets.push_back(bullet);
}