#pragma once
#include "Object.h"

class Score : public IObject
{
public:
	int currentScore = 0;
	std::vector<std::string> digits;
	Score(Transform transform);
	void Render() override;
	void Awake() override;
	void Update(float deltaTime) override;
	std::string GetString(int number);
};

