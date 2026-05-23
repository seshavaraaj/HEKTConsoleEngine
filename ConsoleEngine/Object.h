#pragma once
#include "Main.h"
#include "Screen.h"
#include <Windows.h>
#include <string>
#include <vector>

struct Transform
{
    float positionX = 0;
    float positionY = 0;
};

struct Sprite
{
    std::string Art = "";
    WORD Color = White;
	int Width = 0;
	int Height = 0;
};

class IObject
{
public:
    Transform transform;
	Sprite sprite;
	std::string tag = "";
	std::vector<IObject*> collidingObjects;
	std::vector<IObject*> previousCollidingObjects;

	virtual void Render() = 0;

	virtual void Awake() = 0;

	virtual void Update(float deltaTime) = 0;

	virtual ~IObject();

    int GetTransformX()
    {
        return (int)transform.positionX;
    }

    int GetTransformY()
    {
        return (int)transform.positionY;
    }

    void BoundMove(float deltaX, float deltaY, int width, int height);

    bool IsOutOfBounds(int width, int height);

	bool CheckCollision(IObject* other);

    bool IsCollidingWithAny();

    IObject* IsCollidingWith(std::string tag);

	IObject* IsEnteredCollisionWith(std::string tag);

	IObject* IsExitedCollisionWith(std::string tag);

    IObject();
};