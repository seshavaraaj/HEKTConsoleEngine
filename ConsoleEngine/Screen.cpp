#include <iostream>
#include <windows.h>
#include "Screen.h"

HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
WORD Color[1] = { FOREGROUND_RED };

void SetFullscreen()
{
    keybd_event(VK_F11, 0, 0, 0);
    keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);

	HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_MAXIMIZE);

    while (!IsWindowFullscreen(consoleWindow));
}

void FillScreenWithCharacter(char32_t character)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hOut, &csbi);
    DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD topLeft = {0, 0};
    DWORD charsWritten;

    FillConsoleOutputCharacter(hOut, character, consoleSize, topLeft, &charsWritten);
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, consoleSize, topLeft, &charsWritten);
    SetConsoleCursorPosition(hOut, topLeft);
}

bool IsWindowFullscreen(HWND hwnd)
{
    WINDOWPLACEMENT wp{};
    wp.length = sizeof(WINDOWPLACEMENT);

    GetWindowPlacement(hwnd, &wp);

    return wp.showCmd == SW_MAXIMIZE;
}

void WriteCharacterAtPosition(char32_t character, COORD position)
{
    CHAR_INFO ci;

    SMALL_RECT rect = {
        position.X,
        position.Y,
        position.X,
        position.Y
    };

    COORD size = { 1,1 };
	COORD zero = { 0,0 };

	ReadConsoleOutput(hOut, &ci, size, zero, &rect);

    ci.Char.UnicodeChar = character;

	WriteConsoleOutput(hOut, &ci, size, zero, &rect);
}

void LockHideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}