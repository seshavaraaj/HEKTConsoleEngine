#include "Renderer.h"
#include <iostream>

namespace HEKTConsoleEngine
{
	Renderer::Renderer()
    {
		int visibleWidth, visibleHeight;
        CreateCustomBuffer();
		GetVisibleConsoleSize(visibleWidth, visibleHeight);
		SetupCustomBuffer(visibleWidth, visibleHeight);
		ClearScreenBuffer();
		HideConsoleCursor();
    }

    Renderer::~Renderer()
    {
        if (screenBuffer)
        {
			delete[] screenBuffer;
			screenBuffer = nullptr;
        }
        if (hOut != INVALID_HANDLE_VALUE)
        {
            CloseHandle(hOut);
            hOut = INVALID_HANDLE_VALUE;
        }
	}

	void Renderer::CreateCustomBuffer()
	{
		hOut = CreateConsoleScreenBuffer(
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            CONSOLE_TEXTMODE_BUFFER,
            NULL
        );
		SetConsoleActiveScreenBuffer(hOut);
	}

    void Renderer::SetupCustomBuffer(int width, int height)
    {
        screenWidth = width;
        screenHeight = height;

        if (screenBuffer)
        {
            delete[] screenBuffer;
			screenBuffer = nullptr;
        }

		screenBuffer = new CHAR_INFO[screenWidth * screenHeight + 1];

		short w = (short)screenWidth;
		short h = (short)screenHeight;

		CONSOLE_SCREEN_BUFFER_INFO csbi;

        if (GetConsoleScreenBufferInfo(hOut, &csbi))
        {
			short tempW = (w > csbi.dwSize.X) ? w : csbi.dwSize.X;
			short tempH = (h > csbi.dwSize.Y) ? h : csbi.dwSize.Y;
			SetConsoleScreenBufferSize(hOut, { tempW, tempH });

			SMALL_RECT rect = { 0, 0, (short)(w - 1), (short)(h - 1) };
			SetConsoleWindowInfo(hOut, TRUE, &rect);

			SetConsoleScreenBufferSize(hOut, { w, h });
        }
	}

    void Renderer::ClearScreenBuffer()
    {
		int count = screenWidth * screenHeight;
        CHAR_INFO fill;
        fill.Char.UnicodeChar = ' ';
        fill.Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

        for (size_t i = 0; i < count; ++i)
            screenBuffer[i] = fill;
	}

    void Renderer::GetVisibleConsoleSize(int& width, int& height)
    {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
        
        if (!GetConsoleScreenBufferInfo(hOut, &csbi))
            return;
        
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }

    void Renderer::RenderScreenBuffer()
    {
		writeRegion = { 0, 0, (short)(screenWidth - 1), (short)(screenHeight - 1) };
        WriteConsoleOutputW(hOut, screenBuffer, { (SHORT)screenWidth, (SHORT)screenHeight }, { 0, 0 }, &writeRegion);
	}

    void Renderer::HandleResize()
    {
		int currentWidth, currentHeight;
        GetVisibleConsoleSize(currentWidth, currentHeight);

        if (currentWidth <= 0 || currentHeight <= 0)
			return;

        if (currentWidth != screenWidth || currentHeight != screenHeight)
        {
            SetupCustomBuffer(currentWidth, currentHeight);
			ClearScreenBuffer();

            // 1. Physically overwrite any residual characters living in the active hardware buffer
            DWORD charsWritten;
            COORD home = { 0, 0 };
            FillConsoleOutputCharacterW(hOut, L' ', currentWidth * currentHeight, home, &charsWritten);
            FillConsoleOutputAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, currentWidth * currentHeight, home, &charsWritten);

            // 2. Hide the Scrollbar UI on the console Window bounds
            HWND consoleWindow = GetConsoleWindow();
            if (consoleWindow != NULL)
            {
                ShowScrollBar(consoleWindow, SB_BOTH, FALSE);
            }

            // 3. Enable Virtual Terminal Processing to clear Windows Terminal Scrollback History
            DWORD consoleMode;
            GetConsoleMode(hOut, &consoleMode);
            SetConsoleMode(hOut, consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

            // Write ANSI escape sequences: 
            // \x1b[2J  -> Clears viewport
            // \x1b[3J  -> Clears scrollback history (Destroys ghost frames)
            // \x1b[H   -> Resets cursor to home
            DWORD written;
            WriteConsoleW(hOut, L"\x1b[2J\x1b[3J\x1b[H", 11, &written, NULL);

            // Restore previous mode
            SetConsoleMode(hOut, consoleMode);
		}
    }

    void Renderer::CopyToScreenBuffer(std::string text)
    {
        size_t length = text.length();
        if (length > screenWidth * screenHeight)
            length = screenWidth * screenHeight;
		memcpy(screenBuffer, text.c_str(), length);
	}

    void Renderer::SetBufferChar(int x, int y, wchar_t c, WORD color)
    {
        if (x < 0 || x >= screenWidth || y < 0 || y >= screenHeight)
            return;
		screenBuffer[y * screenWidth + x].Char.UnicodeChar = c;
		screenBuffer[y * screenWidth + x].Attributes = color;
	}
    
    void Renderer::SetBufferString(int x, int y, int width, int height, const std::wstring& str, WORD color)
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

    void Renderer::SetBufferString(int x, int y, int width, int height, const std::wstring& str, WORD* colors)
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

    void Renderer::SetBufferString(int x, int y, const std::wstring& str, WORD color)
    {
        int currentX = x;
        int currentY = y;
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == '\n')
            {
                currentY++;
                currentX = x;
                continue;
            }
            SetBufferChar(currentX, currentY, str[(int)i], color);
            currentX++;
        }
    }

    void Renderer::HideConsoleCursor()
    {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hOut, &cursorInfo);
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(hOut, &cursorInfo);
	}
}