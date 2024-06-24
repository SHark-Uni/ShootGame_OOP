#include "TitleScene.h"
#include "ScreenBuffer.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "SceneTypeId.h"

#include <windows.h>

using namespace ShootingGame;

TitleScene::TitleScene()
	: BaseScene(static_cast<int>(eSceneTypeId::TITLE_SCENE))
	, mMenuCursorX(MENU_CURSOR_X)
	, mMenuCursorY(START_MENU_CURSOR_Y)

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
	s.DrawString(L"시작하기", 25, START_MENU_CURSOR_Y);
	s.DrawString(L"종료하기", 25, START_MENU_CURSOR_Y + 1);

	s.DrawSprite(24, START_MENU_CURSOR_Y, L'>');
}

bool TitleScene::Update()
{
	//키 입력
	DrawMainMenu();
	if (GetAsyncKeyState(VK_DOWN))
	{
		if (mMenuCursorY < EXIT_MENU_CURSOR_Y)
		{
			++mMenuCursorY;
		}
	}
	if (GetAsyncKeyState(VK_UP))
	{
		if (mMenuCursorY >= EXIT_MENU_CURSOR_Y)
		{
			--mMenuCursorY;
		}
	}

	if (GetAsyncKeyState(VK_RETURN))
	{	
		//LOADSCENE
		if (mMenuCursorY == START_MENU_CURSOR_Y)
		{
			//이런느낌으로?
			SceneManager::GetInstance().LoadScene(new GameScene());
			return true;
		}
		else if (mMenuCursorY == EXIT_MENU_CURSOR_Y)
		{
			//main문의 밖으로 빼고싶은데..
			return false;
		}
	}
	return true;
}