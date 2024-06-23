#pragma warning ( disable : 26495 )
#include "ScreenBuffer.h"

#include <stdio.h>
#include <wchar.h>
using namespace ShootingGame;

ScreenBuffer ScreenBuffer::_singleton;

ScreenBuffer::ScreenBuffer()
{
	cs_Initial();
	for (size_t i = 0; i < MAX_SCREEN_HEIGHT; i++)
	{
		wmemset(mScreenBuffer[i], L' ', MAX_SCREEN_WIDTH);
		mScreenBuffer[i][MAX_SCREEN_WIDTH - 1] = L'\0';
	}
	
}

ScreenBuffer::~ScreenBuffer()
{

}

void ScreenBuffer::DrawString(const WCHAR* str, int x, int y)
{
	if (x < 0 || x >= MAX_SCREEN_WIDTH - 1 || y < 0 || y >= MAX_SCREEN_HEIGHT)
		return;
	size_t TextLength = wcslen(str);
	// 화면을 넘어가는 경우 짤라주자
	if ((x + TextLength) >= MAX_SCREEN_WIDTH - 1)
	{
		TextLength = (MAX_SCREEN_WIDTH - 1) - x;
	}
	wcsncpy_s(mScreenBuffer[y], str, TextLength);
}

void ScreenBuffer::DrawSprite(int iX, int iY, WCHAR chSprite)
{
	if (iX < 0 || iY < 0 || iX >= MAX_SCREEN_WIDTH - 1 || iY >= MAX_SCREEN_HEIGHT)
		return;

	mScreenBuffer[iY][iX] = chSprite;
}

void ScreenBuffer::Clear()
{
	for (size_t i = 0; i < MAX_SCREEN_HEIGHT; i++)
	{
		wmemset(mScreenBuffer[i], L' ', MAX_SCREEN_WIDTH);
		mScreenBuffer[i][MAX_SCREEN_WIDTH - 1] = L'\0';
	}
}

ScreenBuffer& ScreenBuffer::GetInstance()
{
	return _singleton;
}

void ScreenBuffer::Flip()
{
	int iCnt;
	for (iCnt = 0; iCnt < MAX_SCREEN_HEIGHT; iCnt++)
	{
		cs_MoveCursor(0, iCnt);
		wprintf(mScreenBuffer[iCnt]);
	}
}

void ScreenBuffer::cs_Initial()
{
	CONSOLE_CURSOR_INFO stConsoleCursor;

	stConsoleCursor.bVisible = FALSE;
	stConsoleCursor.dwSize = 1;

	mConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(mConsole, &stConsoleCursor);
}

void ScreenBuffer::cs_MoveCursor(int PosX, int PosY)
{
	COORD stCoord;
	stCoord.X = PosX;
	stCoord.Y = PosY;
	SetConsoleCursorPosition(mConsole, stCoord);
}




