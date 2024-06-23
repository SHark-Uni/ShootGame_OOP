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
	//���� �׸���
	s.DrawString(L"SLUG ver2",25, 5);
	s.DrawString(L"�����ϱ�", 25, mMenuCursorX);
	s.DrawString(L"�����ϱ�", 25, mMenuCursorY);

}

bool TitleScene::Update()
{
	//Ű �Է�
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
			//�̷���������?
			SceneManager::GetInstance().LoadScene(new GameScene(0));
			return true;
		}
		else if (mMenuCursorY == EXIT_MENU_CURSOR)
		{
			//main���� ������ ���������..
			return false;
		}
	}
	return true;
}