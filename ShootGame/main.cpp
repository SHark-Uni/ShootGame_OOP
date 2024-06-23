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
	SceneManager& SCENE_MANAGER = SceneManager::GetInstance();
	InitializeManager& INIT_MANAGER = 
	// 근데 이건 어디서 해주지 ?ㅋㅋㅋ 
	// InitializerManager.CreateInitailzier(new GameEntry())
	// InitializerManager.Init();
	ASSETLOADER.Load();

	DWORD nextTick = TIMER.GetMilliSeconds();
	DWORD SleepTime;
	while (1)
	{
		SCENE_MANAGER.Run();
		if (SCENE_MANAGER.RequestExitGame())
		{
			goto RETURNS;
		}
		CONSOLE.Clear();
		GM.Update();
		GM.DestroyColliedObject();

		nextTick += TIMER.GetFrame();
		SleepTime = nextTick - TIMER.GetMilliSeconds();
		if (SleepTime >= 0)
		{
			Sleep(SleepTime);
		}
		GM.Draw();
		CONSOLE.Flip();
	}

RETURNS:
	ASSETLOADER.DestroyAllLoader();
	GM.DestroyAllObject();
#endif
}

