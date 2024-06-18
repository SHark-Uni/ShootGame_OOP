#pragma once

#include "LinkedList.h"
#include "GameBaseObject.h"

namespace ShootingGame
{
	class GameObjectManager
	{
	public:
		void CreateObject(GameBaseObject* obj);
		void DestroyObject();

		static GameObjectManager& GetInstance();

		void CheckCollision();

		void Update();
		void Draw();
	private:
		static GameObjectManager _GameManagers;
		GameObjectManager();
		~GameObjectManager();

		GameObjectManager(const GameObjectManager& other) = delete;
		GameObjectManager(GameObjectManager&& rhs) = delete;
		GameObjectManager& operator=(const GameObjectManager& rhs) = delete;
		GameObjectManager& operator=(GameObjectManager&& rhs) = delete;

		LinkedList<GameBaseObject*> mList;
	};
}