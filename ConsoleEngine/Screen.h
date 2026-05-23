#pragma once
#include <windows.h>
#include <string>

enum Color
{
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    White = 15
};


extern const int SCREEN_LOWER_BOUNDARY_X;
extern const int SCREEN_LOWER_BOUNDARY_Y;
extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;

extern char* screenBuffer;
extern WORD* colorBuffer;
extern DWORD dwBytesWritten;

extern HANDLE hOut;

extern void SetFullscreen();

extern bool IsWindowFullscreen(HWND hwnd);

extern void LockHideCursor();

extern void SetupCustomBuffer();

extern void RenderScreenBuffer();

extern void RenderColorBuffer();

extern void ClearScreenBuffer();

extern void SetBufferChar(int x, int y, char c, WORD color);

extern void SetBufferString(int x, int y, int width, int height, std::string& str, WORD color);

extern void SetBufferString(int x, int y, int width, int height, std::string& str, WORD* colors);