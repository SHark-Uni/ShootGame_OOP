#include "ClearScene.h"
#include "TitleScene.h"

#include "SceneTypeId.h"
#include "SceneManager.h"
#include "GameObjectManager.h"
#include "ScreenBuffer.h"


using namespace ShootingGame;

void ClearScene::DrawClearScreen()
{
	ScreenBuffer& s = ScreenBuffer::GetInstance();

	s.DrawString(L"GO TO TITLE Press Y/N", MENU_CURSOR_X, TITLE_MENU);
	s.DrawSprite(MENU_CURSOR_X - 1, TITLE_MENU, L'>');
}

ClearScene::ClearScene()
	:BaseScene(static_cast<int>(eSceneTypeId::CLEAR_SCENE))
{

}

ClearScene::~ClearScene()
{
	
}

bool ClearScene::Update()
{
	DrawClearScreen();
	SceneManager& sm = SceneManager::GetInstance();
	if (GetAsyncKeyState('Y'))
	{
		sm.LoadScene(new TitleScene());
	}
	return true;
}