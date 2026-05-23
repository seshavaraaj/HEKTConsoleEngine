#include "Bullet.h"
#include "Screen.h"
#include "Main.h"
#include "Enemy.h"
#include "SpaceShip.h"

Bullet::Bullet(Transform transform) : IObject()
{
	this->transform = transform;
	sprite.Height = 1;
	sprite.Width = 1;
	sprite.Color = Yellow;
}

void Bullet::Render()
{
	SetBufferChar(GetTransformX(), GetTransformY(), '\xFE', sprite.Color);
}

void Bullet::Update(float deltaTime)
{
	if (IsOutOfBounds(sprite.Width, sprite.Height))
	{
		delete this;
		return;
	}

	Move(deltaTime);

	Enemy* collidedEnemy = dynamic_cast<Enemy*>(IsEnteredCollisionWith("Enemy"));
	if (collidedEnemy != nullptr)
	{
		collidedEnemy->health -= 20;
		delete this;
		return;
	}

	SpaceShip* collidedSpaceShip = dynamic_cast<SpaceShip*>(IsEnteredCollisionWith("Player"));
	if (collidedSpaceShip != nullptr)
	{
		collidedSpaceShip->health -= 20;
		delete this;
		return;
	}
}

void Bullet::Awake()
{
}

void Bullet::Move(float deltaTime)
{
	if (direction == Up)
	{
		transform.positionY -= speed * deltaTime;
	}
	else if (direction == Down)
	{
		transform.positionY += speed * deltaTime;
	}
	else if (direction == Left)
	{
		transform.positionX -= speed * deltaTime;
	}
	else if (direction == Right)
	{
		transform.positionX += speed * deltaTime;
	}
}