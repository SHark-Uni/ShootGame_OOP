#include "AssetLoaderManager.h"

using namespace ShootingGame;

AssetLoaderManager AssetLoaderManager::_AssetLoader;

AssetLoaderManager::AssetLoaderManager()
	:mLoader(nullptr)
{

}

AssetLoaderManager::~AssetLoaderManager()
{
	delete mLoader;
}

void AssetLoaderManager::CreateLoader(BaseAssetLoader* fileLoader)
{
	mLoader = fileLoader;
}

BaseAssetLoader* AssetLoaderManager::GetLoader() const
{
	return mLoader;
}


void AssetLoaderManager::Load()
{
	assert(mLoader != nullptr);
	mLoader->Load();
}

AssetLoaderManager& AssetLoaderManager::GetInstance()
{
	return _AssetLoader;
}