#pragma once

#include <windows.h>

#define MAX_SCREEN_HEIGHT (24)
#define MAX_SCREEN_WIDTH (81)
#define MAX_MOVABLE_WIDTH_INDEX (79)
#define MAX_MOVABLE_HEIGHT_INDEX (23)

namespace ShootingGame
{
	class ScreenBuffer
	{
	public:
		static ScreenBuffer& GetInstance();
		void DrawSprite(int x, int y, WCHAR sprite);
		void DrawString(const WCHAR* str, int x, int y);

		void Clear();
		void Flip();
	private:
		ScreenBuffer();
		~ScreenBuffer();
		ScreenBuffer(const ScreenBuffer&) = delete; 
		ScreenBuffer(ScreenBuffer&&) noexcept = delete;
		ScreenBuffer& operator=(const ScreenBuffer& ) = delete;
		ScreenBuffer& operator=(ScreenBuffer&& ) noexcept = delete;

		static ScreenBuffer _singleton;
		WCHAR mScreenBuffer[MAX_SCREEN_HEIGHT][MAX_SCREEN_WIDTH];
		HANDLE mConsole;

		void cs_Initial();
		void cs_MoveCursor(int PosX, int PosY);
	};
}