#include "GameObjectManager.h"

using namespace ShootingGame;

GameObjectManager GameObjectManager::_GameManagers;

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{
	
}

GameObjectManager& GameObjectManager::GetInstance()
{
	return _GameManagers;
}

void GameObjectManager::CreateObject(GameBaseObject* obj)
{
	mList.push_back(obj);
}

void GameObjectManager::DestroyObject()
{
	LinkedList<GameBaseObject*>::iterator iter;
	for (iter = mList.begin(); iter != mList.end(); ++iter)
	{
		delete (*iter);
	}
	mList.clear();
}

void GameObjectManager::CheckCollision()
{
	LinkedList<GameBaseObject*>::iterator iter;
	for (iter = mList.begin(); iter != mList.end(); )
	{
		if ((*iter)->mIsAlive == false) 
		{
			delete (*iter);
			iter = mList.erase(iter);
			continue;
		}
		++iter;
	}
}

void GameObjectManager::Update()
{
	LinkedList<GameBaseObject*>::iterator iter;
	for (iter = mList.begin(); iter != mList.end(); ++iter)
	{
		(*iter)->Update();
	}
}

void GameObjectManager::Draw()
{
	LinkedList<GameBaseObject*>::iterator iter;
	for (iter = mList.begin(); iter != mList.end(); ++iter)
	{
		(*iter)->Draw();
	}
}

