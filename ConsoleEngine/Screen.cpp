#include <iostream>
#include <windows.h>
#include "Screen.h"

int const SCREEN_HEIGHT = 56; //56
int const SCREEN_WIDTH = 209; //209

//y * width + x
char* screenBuffer = new char[SCREEN_WIDTH * SCREEN_HEIGHT + 1];
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

void ClearScreenBuffer()
{
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
    {
        screenBuffer[i] = ' ';
    }
}

void SetBufferChar(int x, int y, char c)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) return;
    screenBuffer[(y * SCREEN_WIDTH) + x] = c;
}