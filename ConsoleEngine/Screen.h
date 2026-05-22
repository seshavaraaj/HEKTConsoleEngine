#pragma once
#include <windows.h>

extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;

extern char* screenBuffer;
extern DWORD dwBytesWritten;

extern HANDLE hOut;

extern void SetFullscreen();

extern bool IsWindowFullscreen(HWND hwnd);

extern void LockHideCursor();

extern void SetupCustomBuffer();

extern void RenderScreenBuffer();

extern void ClearScreenBuffer();

extern void SetBufferChar(int x, int y, char c);