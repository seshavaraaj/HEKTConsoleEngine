#include "Object.h"
#include "Screen.h"
#include "Main.h"
#include <algorithm>

IObject::IObject(Transform transform, Sprite sprite)
{
	IObjects.push_back(this);
	this->transform = transform;
	this->sprite = sprite;
}

IObject::~IObject()
{
	IObjects.erase(std::remove(IObjects.begin(), IObjects.end(), this), IObjects.end());
}