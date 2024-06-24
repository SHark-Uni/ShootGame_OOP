#include "DeadScene.h"
#include "SceneTypeId.h"
#include "ScreenBuffer.h"

#include "GameScene.h"
#include "TitleScene.h"
#include "SceneManager.h"


#include <windows.h>
#include <cassert>

using namespace ShootingGame;

//죽었습니다 화면 표시해주기

// 메인으로 가기 클릭하면, 타이틀 씬으로 전환 
// 종료시 false반환

// 해당 스테이지로 재도전하기?

DeadScene::DeadScene(unsigned int curStage)
	:BaseScene(static_cast<int>(eSceneTypeId::DEAD_SCENE))
	,mDeadStage(curStage)
	,mMenuCursorX(MENU_CURSOR_X)
	,mMenuCursorY(RETRY_MENU)
{
	
}

DeadScene::~DeadScene()
{

}

void DeadScene::DrawDeadScreen()
{
	ScreenBuffer& s = ScreenBuffer::GetInstance();

	s.DrawString(L"죽었씁니다!!", 15, 5);
	
	s.DrawString(L"재도전?", MENU_CURSOR_X, RETRY_MENU);
	s.DrawString(L"메인화면", MENU_CURSOR_X, TITLE_MENU);
	s.DrawString(L"종료하기", MENU_CURSOR_X, EXIT_MENU);

	s.DrawSprite(MENU_CURSOR_X - 1, RETRY_MENU, L'>');
}

bool DeadScene::Update()
{
	DrawDeadScreen();
	SceneManager& sm = SceneManager::GetInstance();
	if (GetAsyncKeyState(VK_DOWN))
	{
		if (mMenuCursorY < EXIT_MENU)
		{
			++mMenuCursorY;
		}
	}

	if (GetAsyncKeyState(VK_UP))
	{
		if (mMenuCursorY > RETRY_MENU)
		{
			--mMenuCursorY;
		}
	}

	if (GetAsyncKeyState(VK_RETURN))
	{
		switch (mMenuCursorY)
		{
			//죽었던 스테이지 재시작
		case RETRY_MENU:
			sm.LoadScene(new GameScene(mDeadStage));
			break;
		case TITLE_MENU:
			sm.LoadScene(new TitleScene());
			break;
		case EXIT_MENU:
			return false;
		default:
			assert(false);
			break;
		}
	}

	return true;
}