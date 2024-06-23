#include "TitleScene.h"
#include "ScreenBuffer.h"
#include "SceneManager.h"
#include "GameScene.h"

#include <windows.h>

using namespace ShootingGame;

TitleScene::TitleScene()
	:mMenuCursorX(25)
	, mMenuCursorY(15)

{

}

TitleScene::~TitleScene()
{

}

void TitleScene::DrawMainMenu()
{
	ScreenBuffer& s = ScreenBuffer::GetInstance();
	//제목 그리기
	s.DrawString(L"SLUG ver2",25, 5);
	s.DrawString(L"시작하기", 25, mMenuCursorX);
	s.DrawString(L"종료하기", 25, mMenuCursorY);

}

bool TitleScene::Update()
{
	//키 입력
	DrawMainMenu();
	if (GetAsyncKeyState(VK_DOWN))
	{
		if (mMenuCursorY < EXIT_MENU_CURSOR)
		{
			++mMenuCursorY;
		}
	}
	if (GetAsyncKeyState(VK_UP))
	{
		if (mMenuCursorY >= EXIT_MENU_CURSOR)
		{
			--mMenuCursorY;
		}
	}

	if (GetAsyncKeyState(VK_RETURN))
	{	
		//LOADSCENE
		if (mMenuCursorY == START_MENU_CURSOR)
		{
			//이런느낌으로?
			SceneManager::GetInstance().LoadScene(new GameScene(0));
			return true;
		}
		else if (mMenuCursorY == EXIT_MENU_CURSOR)
		{
			//main문의 밖으로 빼고싶은데..
			return false;
		}
	}
	return true;
}