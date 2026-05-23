#include "Object.h"
#include "Main.h"
#include "Screen.h"
#include <vector>

IObject::IObject()
{
	IObjects.push_back(this);
}

IObject::~IObject()
{
	IObjects.erase(std::remove(IObjects.begin(), IObjects.end(), this), IObjects.end());
}

void IObject::BoundMove(float deltaX, float deltaY, int width, int height)
{
	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;
	float newX = transform.positionX + deltaX;
	float newY = transform.positionY + deltaY;
	if (newX < SCREEN_LOWER_BOUNDARY_X + halfWidth) newX = SCREEN_LOWER_BOUNDARY_X + halfWidth;
	if (newX > SCREEN_WIDTH - halfWidth) newX = SCREEN_WIDTH - halfWidth;
	if (newY < SCREEN_LOWER_BOUNDARY_Y + halfHeight) newY = SCREEN_LOWER_BOUNDARY_Y + halfHeight;
	if (newY > SCREEN_WIDTH - halfHeight) newY = SCREEN_WIDTH - halfHeight;
	transform.positionX = newX;
	transform.positionY = newY;
}

bool IObject::IsOutOfBounds(int width, int height)
{
	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;
	if (SCREEN_LOWER_BOUNDARY_X > transform.positionX + halfWidth ||
		SCREEN_WIDTH < transform.positionX - halfWidth ||
		SCREEN_LOWER_BOUNDARY_Y > transform.positionY + halfHeight ||
		SCREEN_HEIGHT < transform.positionY - halfHeight)
	{
		return true;
	}
	return false;
}

bool IObject::CheckCollision(IObject* other)
{
	float thisHalfWidth = sprite.Width / 2.0f;
	float thisHalfHeight = sprite.Height / 2.0f;
	float otherHalfWidth = other->sprite.Width / 2.0f;
	float otherHalfHeight = other->sprite.Height / 2.0f;
	if (transform.positionX + thisHalfWidth < other->transform.positionX - otherHalfWidth ||
		transform.positionX - thisHalfWidth > other->transform.positionX + otherHalfWidth ||
		transform.positionY + thisHalfHeight < other->transform.positionY - otherHalfHeight ||
		transform.positionY - thisHalfHeight > other->transform.positionY + otherHalfHeight)
	{
		return false;
	}
	collidingObjects.push_back(other);
	return true;
}

bool IObject::IsCollidingWithAny()
{
	return !collidingObjects.empty();
}

IObject* IObject::IsCollidingWith(std::string tag)
{
	for (IObject* collidingObject : collidingObjects)
	{
		if (collidingObject->tag == tag) return collidingObject;
	}
	return nullptr;
}

IObject* IObject::IsEnteredCollisionWith(std::string tag)
{
	for (IObject* collidingObject : collidingObjects)
	{
		if (collidingObject->tag == tag)
		{
			bool wasColliding = false;
			for (IObject* previousCollidingObject : previousCollidingObjects)
			{
				if (previousCollidingObject == collidingObject)
				{
					wasColliding = true;
					break;
				}
			}
			if (!wasColliding) return collidingObject;
		}
	}
	return nullptr;
}

IObject* IObject::IsExitedCollisionWith(std::string tag)
{
	for (IObject* previousCollidingObject : previousCollidingObjects)
	{
		if (previousCollidingObject->tag == tag)
		{
			bool isColliding = false;
			for (IObject* collidingObject : collidingObjects)
			{
				if (collidingObject == previousCollidingObject)
				{
					isColliding = true;
					break;
				}
			}
			if (!isColliding) return previousCollidingObject;
		}
	}
	return nullptr;
}