#include <windows.h>
#include "GameObjectManager.h"
#include "Player.h"
#include "ScreenBuffer.h"

using namespace ShootingGame;

void GameObjectManagerTest()
{
	GameObjectManager& gm = GameObjectManager::GetInstance();
	ScreenBuffer& screen = ScreenBuffer::GetInstance();

	Player* p = new Player({ 10,5 });
	gm.CreateObject(p);

	while (1)
	{
		screen.Clear();
		gm.Update();

		Sleep(30);
		screen.Flip();
	}
}