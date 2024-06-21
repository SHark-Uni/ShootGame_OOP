#pragma comment (lib, "winmm")
#include <windows.h>
#include <mmsystem.h>

#include "ScreenBuffer.h"
#include "Player.h"
#include "GameObjectManagerTest.h"
#include "PlayerTest.h"
#include "FrameManager.h"
#include "AssetLoaderManager.h"

#include "FIleLoaderTest.h"

using namespace ShootingGame;

int main()
{
	timeBeginPeriod(1);
	LoaderTest();
#if 0
	FrameManager& TIMER = FrameManager::GetInstance();
	GameObjectManager& GM = GameObjectManager::GetInstance();
	ScreenBuffer& CONSOLE = ScreenBuffer::GetInstance();
	AssetLoaderManager& ASSETLOADER = AssetLoaderManager::GetInstance();

	DWORD nextTick = TIMER.GetMilliSeconds();
	DWORD SleepTime;

	ASSETLOADER.Load();
	while (1)
	{
		CONSOLE.Clear();
		GM.Update();
		GM.Draw();
		GM.DestroyColliedObject();

		nextTick += TIMER.GetFrame();
		SleepTime = nextTick - TIMER.GetMilliSeconds();
		if (SleepTime >= 0)
		{
			Sleep(SleepTime);
		}
		CONSOLE.Flip();
	}

	ASSETLOADER.DestroyAllLoader();
	GM.DestroyAllObject();
#endif
}

