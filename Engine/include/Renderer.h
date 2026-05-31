#pragma once
#include <Windows.h>
#include <string>

namespace HEKTConsoleEngine
{
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

    class Renderer
    {
    private:
        int screenWidth = 56; //default place holder
	    int screenHeight = 209; //default place holder

        HANDLE hOut;
        SMALL_RECT writeRegion;
		CHAR_INFO* screenBuffer = nullptr;

    public:
	    Renderer();
	    ~Renderer();
	    void ClearScreenBuffer();
		void RenderScreenBuffer();
		void HideConsoleCursor();
		void HandleResize();
        void CopyToScreenBuffer(std::string text);
		void SetBufferChar(int x, int y, wchar_t c, WORD color);
		void SetBufferString(int x, int y, int width, int height, const std::wstring& str, WORD color);
		void SetBufferString(int x, int y, int width, int height, const std::wstring& str, WORD* colors);
        void SetBufferString(int x, int y, const std::wstring& str, WORD color);

    private:
	    void CreateCustomBuffer();
	    void SetupCustomBuffer(int width, int height);
        void GetVisibleConsoleSize(int& width, int& height);
    };
}