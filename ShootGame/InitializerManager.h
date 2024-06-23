#pragma once

#include "GameInitializer.h"

namespace ShootingGame
{
	class InitializerManager
	{
	public:
		static InitializerManager& GetInstance();
		void CreateInitializer(GameInitiallizer* init);

		void Init();
	private:
		InitializerManager();
		~InitializerManager();

		InitializerManager(const InitializerManager& other) = delete;
		InitializerManager(InitializerManager&& other) = delete;

		InitializerManager& operator=(const InitializerManager& rhs) = delete;
		InitializerManager& operator=(InitializerManager&& rhs) = delete;

		static InitializerManager _Initalizer;
		GameInitiallizer* mInit;
	};

}