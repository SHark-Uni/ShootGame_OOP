#include "AssetLoaderManager.h"
#include "FileLoader.h"
#include "BaseAssetLoader.h"

namespace ShootingGame
{
	inline void LoaderTest()
	{
		AssetLoaderManager& ASSETLOADER = AssetLoaderManager::GetInstance();
		ASSETLOADER.CreateLoader(new FileLoader());

		ASSETLOADER.Load();

	}
}