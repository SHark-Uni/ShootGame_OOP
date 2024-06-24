#pragma comment (lib, "winmm")
#include <windows.h>
#include <mmsystem.h>

#include "ScreenBuffer.h"
#include "Player.h"
#include "GameObjectManagerTest.h"
#include "PlayerTest.h"
#include "FrameManager.h"
#include "SceneManager.h"
#include "AssetLoaderManager.h"
#include "InitializerManager.h"
#include "GameEntry.h"

#include "FIleLoaderTest.h"
#include "FrameManagerTest.h"

using namespace ShootingGame;

int main()
{
	timeBeginPeriod(1);

	FrameManager& TIMER = FrameManager::GetInstance();
	GameObjectManager& GM = GameObjectManager::GetInstance();
	ScreenBuffer& CONSOLE = ScreenBuffer::GetInstance();
	AssetLoaderManager& ASSETLOADER = AssetLoaderManager::GetInstance();
	SceneManager& SCENE_MANAGER = SceneManager::GetInstance();
	InitializerManager& INIT_MANAGER = InitializerManager::GetInstance();

	INIT_MANAGER.CreateInitializer(new GameEntry());
	INIT_MANAGER.Init();

	ASSETLOADER.Load();

	DWORD nextTick = TIMER.GetMilliSeconds();
	DWORD SleepTime;
	while (1)
	{
		CONSOLE.Clear();
		SCENE_MANAGER.Run();
		if (SCENE_MANAGER.RequestExitGame())
		{
			goto RETURNS;
		}
		GM.Update();
		GM.DestroyColliedObject();

		nextTick += TIMER.Get_MS_PER_FRAME();
		SleepTime = nextTick - TIMER.GetMilliSeconds();
		if (SleepTime >= 0)
		{
			Sleep(SleepTime);
		}
		GM.Draw();
		CONSOLE.Flip();
	}

RETURNS:
	GM.DestroyAllObject();
}

