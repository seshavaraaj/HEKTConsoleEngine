#include "Score.h"
#include "Main.h"


Score::Score(Transform transform) : IObject()
{
	this->transform = transform;
	sprite.Art =
		"\xDB\xDF\xDF \xDB\xDF\xDF \xDB\xDF\xDB \xDB\xDF\xDB \xDB\xDF\xDF \xFE\n"  // Row 1
		"\xDF\xDF\xDB \xDB   \xDB \xDB \xDB\xDB\xDF \xDB\xDF\xDF\n"  // Row 2
		"\xDB\xDC\xDB \xDB\xDC\xDC \xDB\xDC\xDB \xDB \xDB \xDB\xDC\xDC \xFE\n";
	sprite.Width = 17;
	sprite.Height = 3;
	sprite.Color = LightBlue;

	digits.push_back(
		"\xDB\xDF\xDB\n"
		"\xDB \xDB\n"
		"\xDB\xDC\xDB\n"
	);
	digits.push_back(
		" \xDB \n"
		" \xDB \n"
		" \xDB \n"
	);
	digits.push_back(
		"\xDF\xDF\xDB\n"
		"\xDB\xDF\xDF\n"
		"\xDB\xDC\xDB\n"
	);
	digits.push_back(
		"\xDF\xDF\xDB\n"
		"\xDF\xDF\xDB\n"
		"\xDB\xDC\xDB\n"
	);
	digits.push_back(
		"\xDB \xDB\n"
		"\xDB\xDF\xDB\n"
		"  \xDB\n"
	);
	digits.push_back(
		"\xDB\xDF\xDF\n"
		"\xDF\xDF\xDB\n"
		"\xDB\xDC\xDB\n"
	);
	digits.push_back(
		"\xDB\xDF\xDF\n"
		"\xDB\xDF\xDB\n"
		"\xDB\xDC\xDB\n"
	);
	digits.push_back(
		"\xDF\xDF\xDB\n"
		"   \xDB\n"
		"   \xDB\n"
	);
	digits.push_back(
		"\xDB\xDF\xDB\n"
		"\xDB\xDF\xDB\n"
		"\xDB\xDC\xDB\n"
	);
	digits.push_back(
		"\xDB\xDF\xDB\n"
		"\xDF\xDF\xDB\n"
		"  \xDB\n"
	);
}

void Score::Render()
{
	SetBufferString(GetTransformX(), GetTransformY(), sprite.Width, sprite.Height, sprite.Art, sprite.Color);
	std::string currentScoreOnes = GetString(this->currentScore%10);
	std::string currentScoreTens = GetString((this->currentScore / 10) % 10);
	SetBufferString(GetTransformX() + 15, GetTransformY(), 3, 3, currentScoreTens, sprite.Color);
	SetBufferString(GetTransformX() + 19, GetTransformY(), 3, 3, currentScoreOnes, sprite.Color);
}

void Score::Awake()
{

}

void Score::Update(float deltaTime)
{
	this->currentScore = score;
}

std::string Score::GetString(int number)
{
	return digits[number];
}