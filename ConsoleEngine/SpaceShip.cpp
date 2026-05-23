#include "SpaceShip.h"
#include "Object.h"
#include "Screen.h"
#include "input.h"
#include "Bullet.h"
#include <vector>

SpaceShip::SpaceShip(Transform transform) : IObject()
{
	this->transform = transform;
	sprite.Art = "  \xDC  \n"
				"\xDC\xDB\xDB\xDB\xDC";
	sprite.Width = 5;
	sprite.Height = 2;
	sprite.Color = White;
	tag = "Player";
}

void SpaceShip::Render()
{
	SetBufferString(GetTransformX(), GetTransformY(), sprite.Width, sprite.Height, sprite.Art, sprite.Color);
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
	if (health <= 0)
	{
		delete this;
		return;
	}

	if (GetKey(VK_LEFT))
	{
		BoundMove(-50 * deltaTime, 0, sprite.Width, sprite.Height);
	}
	if (GetKey(VK_RIGHT))
	{
		BoundMove(50 * deltaTime, 0, sprite.Width, sprite.Height);
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
	Bullet* bullet = new Bullet(Transform{ transform.positionX, transform.positionY - 2 });
	bullets.push_back(bullet);
}