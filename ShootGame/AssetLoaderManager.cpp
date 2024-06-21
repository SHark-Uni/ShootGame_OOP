#include "AssetLoaderManager.h"

using namespace ShootingGame;

AssetLoaderManager AssetLoaderManager::_AssetLoader;

AssetLoaderManager::AssetLoaderManager()
{

}

AssetLoaderManager::~AssetLoaderManager()
{

}

void AssetLoaderManager::CreateLoader(BaseAssetLoader* fileLoader)
{
	mLoaderList.push_back(fileLoader);
}

void AssetLoaderManager::DestroyAllLoader()
{
	LinkedList<BaseAssetLoader*>::iterator iter;

	for (iter = mLoaderList.begin(); iter != mLoaderList.end(); ++iter)
	{
		delete (*iter);
	}
	mLoaderList.clear();
}

void AssetLoaderManager::Load()
{
	LinkedList<BaseAssetLoader*>::iterator iter;
	for (iter = mLoaderList.begin(); iter != mLoaderList.end(); ++iter)
	{
		(*iter)->Load();
	}
}

AssetLoaderManager& AssetLoaderManager::GetInstance()
{
	return _AssetLoader;
}