#include "DeadScene.h"
#include "SceneTypeId.h"
#include "ScreenBuffer.h"

#include "GameScene.h"
#include "TitleScene.h"
#include "SceneManager.h"


#include <windows.h>
#include <cassert>

using namespace ShootingGame;

//�׾����ϴ� ȭ�� ǥ�����ֱ�

// �������� ���� Ŭ���ϸ�, Ÿ��Ʋ ������ ��ȯ 
// ����� false��ȯ

// �ش� ���������� �絵���ϱ�?

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

	s.DrawString(L"�׾����ϴ�!!", 15, 5);
	
	s.DrawString(L"�絵��?", MENU_CURSOR_X, RETRY_MENU);
	s.DrawString(L"����ȭ��", MENU_CURSOR_X, TITLE_MENU);
	s.DrawString(L"�����ϱ�", MENU_CURSOR_X, EXIT_MENU);

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
			//�׾��� �������� �����
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