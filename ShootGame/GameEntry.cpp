#include "GameEntry.h"
#include "InitializerManager.h"
#include "AssetLoaderManager.h"
#include "SceneManager.h"

#include "FileLoader.h"
#include "TitleScene.h"

using namespace ShootingGame;

void GameEntry::Init()
{
	AssetLoaderManager::GetInstance().CreateLoader(new FileLoader());
	SceneManager::GetInstance().LoadScene(new TitleScene());
}
