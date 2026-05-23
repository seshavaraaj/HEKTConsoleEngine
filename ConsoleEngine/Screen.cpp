#include <iostream>
#include <windows.h>
#include "Screen.h"

int const SCREEN_LOWER_BOUNDARY_X = 0;
int const SCREEN_LOWER_BOUNDARY_Y = 0;

int const SCREEN_HEIGHT = 56; //56
int const SCREEN_WIDTH = 209; //209

//y * width + x
char* screenBuffer = new char[SCREEN_WIDTH * SCREEN_HEIGHT + 1];
WORD* colorBuffer = new WORD[SCREEN_WIDTH * SCREEN_HEIGHT + 1];
DWORD dwBytesWritten;

HANDLE hOut = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

void SetFullscreen()
{
	
    keybd_event(VK_F11, 0, 0, 0);
    keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);

	HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_MAXIMIZE);

    while (!IsWindowFullscreen(consoleWindow));
}

bool IsWindowFullscreen(HWND hwnd)
{
    WINDOWPLACEMENT wp{};
    wp.length = sizeof(WINDOWPLACEMENT);

    GetWindowPlacement(hwnd, &wp);

    return wp.showCmd == SW_MAXIMIZE;
}

void LockHideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

void SetupCustomBuffer()
{
    SetConsoleActiveScreenBuffer(hOut);
	dwBytesWritten = 0;
}

void RenderScreenBuffer()
{
	WriteConsoleOutputCharacterA(hOut, screenBuffer, SCREEN_WIDTH * SCREEN_HEIGHT, { 0, 0 }, &dwBytesWritten);
}

void RenderColorBuffer()
{
    WriteConsoleOutputAttribute(hOut, colorBuffer, SCREEN_WIDTH * SCREEN_HEIGHT, { 0, 0 }, &dwBytesWritten);
}

void ClearScreenBuffer()
{
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
    {
        screenBuffer[i] = ' ';
		colorBuffer[i] = Black;
    }
}

void SetBufferChar(int x, int y, char c, WORD color)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) return;
    screenBuffer[(y * SCREEN_WIDTH) + x] = c;
	colorBuffer[(y * SCREEN_WIDTH) + x] = color;
}

void SetBufferString(int x, int y, int width, int height, std::string& str, WORD color)
{
    int halfSpriteWidth = width / 2;
    int halfSpriteHeight = height / 2;
    int calculatedX = x - halfSpriteWidth;
    int calculatedY = y - halfSpriteHeight;
    int currentX = calculatedX;
    int currentY = calculatedY;

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '\n')
        {
            currentY++;
            currentX = calculatedX;
            continue;
        }
        SetBufferChar(currentX, currentY, str[(int)i], color);
        currentX++;
    }
}

void SetBufferString(int x, int y, int width, int height, std::string& str, WORD* colors)
{
	int halfSpriteWidth = width / 2;
	int halfSpriteHeight = height / 2;
    int calculatedX = x - halfSpriteWidth;
    int calculatedY = y - halfSpriteHeight;
    int currentX = calculatedX;
	int currentY = calculatedY;

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '\n')
        {
            currentY++;
            currentX = calculatedX;
            continue;
        }
        SetBufferChar(currentX, currentY, str[(int)i], colors[i]);
        currentX++;
	}
}