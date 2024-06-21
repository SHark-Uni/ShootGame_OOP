#pragma once

namespace ShootingGame
{
	class BaseAssetLoader
	{
	public:
		virtual void Load() = 0;
		virtual ~BaseAssetLoader()
		{
		}
	};
}