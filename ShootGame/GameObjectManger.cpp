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

void GameObjectManager::DestroyAllObject()
{
	LinkedList<GameBaseObject*>::iterator iter;
	for (iter = mList.begin(); iter != mList.end(); ++iter)
	{
		delete (*iter);
	}
	mList.clear();
}

void GameObjectManager::DestroyColliedObject()
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
	LinkedList<GameBaseObject*>::iterator curObject;
	LinkedList<GameBaseObject*>::iterator targetObject;
	for (curObject = mList.begin(); curObject != mList.end(); ++curObject)
	{
		targetObject = curObject;
		(*curObject)->Update();

		for (++targetObject; targetObject != mList.end(); ++targetObject)
		{
			(*curObject)->OnCollision((*targetObject));
			(*targetObject)->OnCollision((*curObject));
		}
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

