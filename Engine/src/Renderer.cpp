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
    }

    Renderer::~Renderer()
    {
        if (screenBuffer)
        {
            delete[] screenBuffer;
            screenBuffer = nullptr;
        }
        if (colorBuffer)
        {
            delete[] colorBuffer;
            colorBuffer = nullptr;
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
        if (colorBuffer)
        {
            delete[] colorBuffer;
            colorBuffer = nullptr;
        }
        screenBuffer = new char[screenWidth * screenHeight + 1];
        colorBuffer = new WORD[screenWidth * screenHeight + 1];

		SetConsoleScreenBufferSize(hOut, { (short)screenWidth, (short)screenHeight });
	}

    void Renderer::ClearScreenBuffer()
    {
        memset(screenBuffer, ' ', screenWidth * screenHeight);
        memset(colorBuffer, (WORD)Color::White, screenWidth * screenHeight * sizeof(WORD));
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
        WriteConsoleOutputCharacterA(hOut, screenBuffer, screenWidth * screenHeight, { 0, 0 }, &dwBytesWritten);
	}

    void Renderer::RenderColorBuffer()
    {
        WriteConsoleOutputAttribute(hOut, colorBuffer, screenWidth * screenHeight, { 0, 0 }, &dwBytesWritten);
	}

    void Renderer::HandleResize()
    {
		int currentWidth, currentHeight;
        GetVisibleConsoleSize(currentWidth, currentHeight);
        if (currentWidth != screenWidth || currentHeight != screenHeight)
        {
            SetupCustomBuffer(currentWidth, currentHeight);
		}
    }

    void Renderer::CopyToScreenBuffer(std::string text)
    {
        size_t length = text.length();
        if (length > screenWidth * screenHeight)
            length = screenWidth * screenHeight;
		memcpy(screenBuffer, text.c_str(), length);
	}
}