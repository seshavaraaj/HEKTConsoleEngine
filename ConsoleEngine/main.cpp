#include "Screen.h"

int main()
{
	LockHideCursor();
	SetFullscreen();
	FillScreenWithCharacter(L'\u2588');
	WriteCharacterAtPosition(L'X', { 10, 10 });
	while (true)
	{

	}
	return 0;
}