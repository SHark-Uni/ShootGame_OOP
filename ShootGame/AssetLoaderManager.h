#pragma once

#include "BaseAssetLoader.h"
#include "LinkedList.h"
namespace ShootingGame
{
	class AssetLoaderManager
	{
	public:
		AssetLoaderManager();
		~AssetLoaderManager();

		static AssetLoaderManager& GetInstance();

		void CreateLoader(BaseAssetLoader* fileLoader);
		BaseAssetLoader* GetLoader() const;
		void Load();
	private:
		AssetLoaderManager(const AssetLoaderManager& other) = delete;
		AssetLoaderManager(AssetLoaderManager&& other) = delete;

		AssetLoaderManager& operator=(const AssetLoaderManager& rhs) = delete;
		AssetLoaderManager& operator=(AssetLoaderManager&& rhs) = delete;

		static AssetLoaderManager _AssetLoader;
		BaseAssetLoader* mLoader;
	};
}