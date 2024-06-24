#pragma once

#include "Player.h"
#include "Enemy.h"
#include "FrameManager.h"
#include "GameObjectManager.h"
#include "ScreenBuffer.h"

using namespace ShootingGame;

void FrameTest()
{
	Player* p = new Player(5, 5);
	Enemy* e = new Enemy(20, 3, 0, 1);
	FrameManager& fr = FrameManager::GetInstance();
	GameObjectManager& gm = GameObjectManager::GetInstance();
	ScreenBuffer& screen = ScreenBuffer::GetInstance();
	AssetLoaderManager& ASSETLOADER = AssetLoaderManager::GetInstance();

	ASSETLOADER.CreateLoader(new FileLoader());
	ASSETLOADER.Load();
	fr.SetFrame(50);

	gm.CreateObject(p);
	gm.CreateObject(e);

	DWORD time = fr.GetMilliSeconds();
	DWORD sleeptime;
	while (1)
	{
		screen.Clear();
		gm.Update();
		gm.Draw();

		gm.DestroyColliedObject();
		sleeptime = time - fr.GetMilliSeconds();
		if (sleeptime >= 0)
		{
			Sleep(sleeptime);
		}
		screen.Flip();
	}
}