#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <algorithm>

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

    enum RenderType
    {
        FullScreen,
        DirtyRect
	};

    class Renderer
    {
    private:
        int screenWidth = 56; //default place holder
	    int screenHeight = 209; //default place holder

        HANDLE hOut;
		CHAR_INFO* screenBuffer = nullptr;
		SMALL_RECT DirtyRect = { 0, 0, 0, 0 };
		SMALL_RECT DirtyRectPrevious = { -1, -1, -1, -1 };
		bool hasDirtyRect = false;

    public:
	    Renderer();
	    ~Renderer();
		void Render();
		void ClearFullScreenBuffer();
		void HideConsoleCursor();
		void HandleResize();
		void SetBufferString(int x, int y, int width, int height, const std::wstring& str, WORD color);
		void SetBufferString(int x, int y, int width, int height, const std::wstring& str, WORD* colors);
		void SetBufferString(int x, int y, const std::wstring& str, WORD colors);
        SMALL_RECT GetDirtyRectPrevious();
		void SetRenderType(RenderType type);

    private:
		RenderType currentRenderType = RenderType::DirtyRect;
        void RenderDirtyRectBuffer();
		void RenderFullScreenBuffer();
		void SetBufferChar(int x, int y, wchar_t c, WORD color);
		void MakeDirtyRect(int top, int left, int bottom, int right);
	    void CreateCustomBuffer();
	    void SetupCustomBuffer(int width, int height);
        void GetVisibleConsoleSize(int& width, int& height);
    };
}