#pragma once
#include <windows.h>

extern HANDLE hOut;

extern void SetFullscreen();

extern void FillScreenWithCharacter(char32_t character);

extern bool IsWindowFullscreen(HWND hwnd);

extern void WriteCharacterAtPosition(char32_t character, COORD position);

extern void LockHideCursor();

extern WORD Color[1];