#include <windows.h>
#include "GameObjectManager.h"
#include "Player.h"
#include "ScreenBuffer.h"

using namespace ShootingGame;

void GameObjectManagerTest()
{
	GameObjectManager& gm = GameObjectManager::GetInstance();
	ScreenBuffer& screen = ScreenBuffer::GetInstance();


	info.x = 10;
	info.y = 10;
	info.atk = 5;
	info.speed = 10;
	info.hp = 5;

	Player* p = new Player({ 10,5,10,20,10 });
	gm.CreateObject(new Player(info));
	gm.CreateObject(p);

	while (1)
	{
		screen.Clear();
		gm.Update();

		Sleep(30);
		screen.Flip();
	}
}