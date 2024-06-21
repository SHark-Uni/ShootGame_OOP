#pragma comment (lib, "winmm")
#include <windows.h>
#include <mmsystem.h>

#include "ScreenBuffer.h"
#include "Player.h"
#include "GameObjectManagerTest.h"
#include "PlayerTest.h"
#include "FrameManager.h"

using namespace ShootingGame;

int main()
{
	timeBeginPeriod(1);
	
	FrameManager& timer = FrameManager::GetInstance();

	DWORD nextTick = timer.GetMilliSeconds();
	DWORD SleepTime;

	while (1)
	{
		nextTick += timer.GetFrame();
		

		GameObjectManager::GetInstance().Update();

		GameObjectManager::GetInstance().Draw();

		GameObjectManager::GetInstance().DestroyColliedObject();
		SleepTime = nextTick - timer.GetMilliSeconds();
		if (SleepTime >= 0)
		{
			Sleep(SleepTime);
		}
	}
}

