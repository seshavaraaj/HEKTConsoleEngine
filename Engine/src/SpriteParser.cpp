#include "SpriteParser.h"

namespace HEKTConsoleEngine
{
	//AI assisted implementation of ParseSprite function, which reads a sprite file and converts its UTF-8 content to a wide string (UTF-16) suitable for Windows console rendering.
	const std::wstring SpriteParser::ParseSprite(const std::string& filePath)
	{
        std::ifstream file(filePath, std::ios::binary);
        if (!file.is_open())
        {
			std::string builtPath = BuildFilePath(filePath);
			file.open(builtPath, std::ios::binary);
			if (!file.is_open())
                return L"";
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string rawUtf8str = buffer.str();

        if (rawUtf8str.empty()) return L"";

        // 2. Normalize newlines: Strip out all '\r' characters so we only have '\n'
        rawUtf8str.erase(std::remove(rawUtf8str.begin(), rawUtf8str.end(), '\r'), rawUtf8str.end());

        // 3. Convert UTF-8 bytes to Windows UTF-16 (std::wstring)
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, &rawUtf8str[0], (int)rawUtf8str.size(), NULL, 0);

        std::wstring wstrTo(size_needed, 0);

        MultiByteToWideChar(CP_UTF8, 0, &rawUtf8str[0], (int)rawUtf8str.size(), &wstrTo[0], size_needed);

        // 4. Filter characters
        wstrTo.erase(std::remove_if(wstrTo.begin(), wstrTo.end(), [](wchar_t c) {
            // Keep Space and Newline
            if (c == L' ' || c == L'\n') return false;

            // Keep standard alphanumeric (a-z, A-Z, 0-9)
            if (iswalnum(c)) return false;

            // Keep Unicode Block Elements range (U+2580 to U+259F)
            if (c >= L'\x2580' && c <= L'\x259F') return false;

            // Keep Box Drawing range (U+2500 to U+257F) - Optional, helpful for console UIs
            if (c >= L'\x2500' && c <= L'\x257F') return false;

			if (c == L'\x25A0') return false;

            // If it is anything else (symbols, emojis, formatting weirdness), remove it
            return true;
            }), wstrTo.end());

        return wstrTo;
	}

    const SpriteComponent SpriteParser::ParseSpriteComponent(const std::string& filePath, WORD color)
    {
        std::wstring spriteData = ParseSprite(filePath);
        int width = 0;
        int height = 0;
        // Calculate width and height based on the sprite data
        size_t pos = 0;
        while (pos < spriteData.length())
        {
            size_t newlinePos = spriteData.find(L'\n', pos);
            if (newlinePos == std::wstring::npos)
                newlinePos = spriteData.length();
            int lineWidth = (int)(newlinePos - pos);
            if (lineWidth > width)
                width = lineWidth;
            height++;
            pos = newlinePos + 1; // Move past the newline
        }
        return SpriteComponent(width, height, spriteData, color);
	}


    std::string SpriteParser::BuildFilePath(const std::string& filePath)
    {
		std::string spriteDir = "assets/sprites/";
        std::string builtPath;

        for (int i = filePath.length() - 1; i > 0; i--)
        {
            if (filePath[i] == '/')
            {
                break;
            }
			builtPath += filePath[i];
		}
		std::reverse(builtPath.begin(), builtPath.end());
		return spriteDir + builtPath;
	}
}