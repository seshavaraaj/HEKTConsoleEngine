#include "Enemy.h"
#include "Object.h"
#include "Screen.h"
#include "Bullet.h"
#include "SpaceShip.h"
#include "Main.h"

Enemy::Enemy(Transform transform) :IObject()
{
	this->transform = transform;
	sprite.Art = "  \xDC\xDC\xDC  \n"
				"\xDC\xDB\xDF\xDB\xDF\xDB\xDC\n"
				"\xDD\xDB\xDF\xDF\xDF\xDB\xDE\n";
	sprite.Width = 7;
	sprite.Height = 3;
	sprite.Color = Red;
	tag = "Enemy";
}

Enemy::~Enemy()
{
}

void Enemy::Render()
{
	SetBufferString(GetTransformX(), GetTransformY(), sprite.Width, sprite.Height, sprite.Art, sprite.Color);
}

void Enemy::Awake()
{
}

void Enemy::Update(float deltaTime)
{
	if (IsEnteredCollisionWith("Bullet"))
	{
		health -= 50;
	}
	if (health <= 0)
	{
		score += 25;
		delete this;
		return;
	}
	Strafe(deltaTime);
	shootIntervalCounter -= deltaTime;
	if (shootIntervalCounter <= 0)
	{
		Shoot();
		shootIntervalCounter = shootInterval;
	}
}

void Enemy::Shoot()
{
	GenerateBullet();
}

void Enemy::GenerateBullet()
{
	Bullet* bullet = new Bullet({ transform.positionX, transform.positionY + 3 });
	bullet->direction = Down;
	bullet->speed = 50;
	bullets.push_back(bullet);
}

void Enemy::Strafe(float deltaTime)
{
	BoundMove(direction * speed * deltaTime, 0, sprite.Width, sprite.Height);
	if (GetTransformX() > SCREEN_WIDTH - 10)
	{
		direction = -1;
	}
	else if (GetTransformX() < 10)
	{
		direction = 1;
	}
}

