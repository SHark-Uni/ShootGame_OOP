#include "GameEntry.h"
#include "InitializerManager.h"
#include "AssetLoaderManager.h"
#include "SceneManager.h"

#include "FileLoader.h"
#include "TitleScene.h"
#include "FrameManager.h"


using namespace ShootingGame;

void GameEntry::Init()
{
	AssetLoaderManager::GetInstance().CreateLoader(new FileLoader());
	SceneManager::GetInstance().CreateScene(new TitleScene());
	FrameManager::GetInstance().SetFrame(50);
}
