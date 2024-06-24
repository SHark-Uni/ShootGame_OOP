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
DeadScene::DeadScene(unsigned int curStage)
	:BaseScene(static_cast<int>(eSceneTypeId::DEAD_SCENE))
	,mDeadStage(curStage)
{
	
}

DeadScene::~DeadScene()
{

}

void DeadScene::DrawDeadScreen()
{
	ScreenBuffer& s = ScreenBuffer::GetInstance();

	s.DrawString(L"!!YOU ARE DEAD!!", 15, 5);
	
	s.DrawString(L"RETRY, Press R", MENU_CURSOR_X, RETRY_MENU);
	s.DrawString(L"GO To TITLE, Press Y", MENU_CURSOR_X, TITLE_MENU);
	s.DrawString(L"EXIT, Press N", MENU_CURSOR_X, EXIT_MENU);

}

bool DeadScene::Update()
{
	DrawDeadScreen();
	SceneManager& sm = SceneManager::GetInstance();
	if (GetAsyncKeyState('R'))
	{
		sm.LoadScene(new GameScene(mDeadStage));
		return true;
	}

	if (GetAsyncKeyState('Y'))
	{
		sm.LoadScene(new TitleScene());
		return true;
	}

	if (GetAsyncKeyState('N'))
	{
		return false;
	}
	return true;
}