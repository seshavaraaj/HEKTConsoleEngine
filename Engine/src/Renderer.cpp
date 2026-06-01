#define NOMINMAX
#include "Renderer.h"
#include <iostream>
#include <algorithm>

namespace HEKTConsoleEngine
{
	Renderer::Renderer()
    {
		int visibleWidth, visibleHeight;
        CreateCustomBuffer();
		GetVisibleConsoleSize(visibleWidth, visibleHeight);
		SetupCustomBuffer(visibleWidth, visibleHeight);
		ClearFullScreenBuffer();
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

    void Renderer::GetVisibleConsoleSize(int& width, int& height)
    {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
        
        if (!GetConsoleScreenBufferInfo(hOut, &csbi))
            return;
        
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }

    void Renderer::Render()
    {
        if (currentRenderType == RenderType::FullScreen)
        {
            RenderFullScreenBuffer();
        }
        else
        {
            RenderDirtyRectBuffer();
        }
    }

    void Renderer::RenderFullScreenBuffer()
    {
        COORD bufferSize = { (SHORT)screenWidth, (SHORT)screenHeight };
        COORD bufCoord = { 0, 0 };
        SMALL_RECT writeRegion = { 0, 0, (SHORT)(screenWidth - 1), (SHORT)(screenHeight - 1) };
        WriteConsoleOutputW(hOut, screenBuffer, bufferSize, bufCoord, &writeRegion);
	}

    void Renderer::RenderDirtyRectBuffer()
    {
        SMALL_RECT currentFrameDirtyRect = DirtyRect;
        bool currentHasDirty = hasDirtyRect;

		MakeDirtyRect(DirtyRectPrevious.Top, DirtyRectPrevious.Left, DirtyRectPrevious.Bottom, DirtyRectPrevious.Right);

        if (hasDirtyRect)
        {
            COORD bufferSize = { (SHORT)screenWidth, (SHORT)screenHeight };
            COORD bufCoord = { DirtyRect.Left, DirtyRect.Top };
            WriteConsoleOutputW(hOut, screenBuffer, bufferSize, bufCoord, &DirtyRect);
        }

        if (currentHasDirty)
        {
		    DirtyRectPrevious = currentFrameDirtyRect;
        }
        else
        {
            DirtyRectPrevious = { -1, -1, -1, -1 }; // Empty state
        }
        
        hasDirtyRect = false;
    }

    void Renderer::ClearFullScreenBuffer()
    {
        int count = screenWidth * screenHeight;
        
        // A CHAR_INFO is exactly 32 bits (struct size is 4 bytes).
        // The character (L' ' = 0x0020) takes the lower 16 bits.
        // The color (White = 0x0007) takes the upper 16 bits.
        // We pack this into a single 32-bit integer: 0x00070020
        DWORD fillValue = 0x00070020;
        
        // Cast buffer to DWORD and fill. This forces 32-bit (or vectorized 128/256-bit) assignments.
        DWORD* ptr = reinterpret_cast<DWORD*>(screenBuffer);
        std::fill_n(ptr, count, fillValue);
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
			ClearFullScreenBuffer();

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

    void Renderer::SetBufferChar(int x, int y, wchar_t c, WORD color)
    {
        if (x < 0 || x >= screenWidth || y < 0 || y >= screenHeight)
            return;
        if (c == ' ')
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
		MakeDirtyRect(calculatedY, calculatedX, calculatedY + height, calculatedX + width);
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
		MakeDirtyRect(calculatedY, calculatedX, calculatedY + height, calculatedX + width);
	}

    void Renderer::SetBufferString(int x, int y, const std::wstring& str, WORD color)
    {
        int currentX = x;
        int currentY = y;
        int right = 0;
        int bottom = 0;
        for (int i = 0; i < str.length() - 1; i++)
        {
            if (str[i] == '\n')
            {
                currentY++;
				right = std::max(right, currentX);
                currentX = x;
                continue;
            }
            SetBufferChar(currentX, currentY, str[(int)i], color);
            currentX++;
        }
		bottom = currentY + 1;
		MakeDirtyRect(y, x, bottom, right);
    }

    void Renderer::MakeDirtyRect(int top, int left, int bottom, int right)
    {
        if (currentRenderType != RenderType::DirtyRect)
			return;
        if (right < 0 || left >= screenWidth + 1 || bottom < 0 || top >= screenHeight + 1)
			return;
        
		if (top < 0) top = 0;
		if (left < 0) left = 0;
		if (bottom >= screenHeight) bottom = screenHeight - 1;
		if (right >= screenWidth) right = screenWidth - 1;

        if (!hasDirtyRect)
        {
            DirtyRect.Top = (short)top;
            DirtyRect.Left = (short)left;
            DirtyRect.Bottom = (short)bottom;
            DirtyRect.Right = (short)right;
            hasDirtyRect = true;
        }
        else
        {
            DirtyRect.Top = std::min(DirtyRect.Top, (short)top);
            DirtyRect.Left = std::min(DirtyRect.Left, (short)left);
            DirtyRect.Bottom = std::max(DirtyRect.Bottom, (short)bottom);
            DirtyRect.Right = std::max(DirtyRect.Right, (short)right);
        }
	}

    void Renderer::HideConsoleCursor()
    {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hOut, &cursorInfo);
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(hOut, &cursorInfo);
	}

    SMALL_RECT Renderer::GetDirtyRectPrevious()
    {
        return DirtyRectPrevious;
	}

    void Renderer::SetRenderType(RenderType type)
    {
        currentRenderType = type;
	}
}