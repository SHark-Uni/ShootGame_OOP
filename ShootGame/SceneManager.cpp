#include "SceneManager.h"

using namespace ShootingGame;

SceneManager SceneManager::_SceneManager;

SceneManager::SceneManager()
	:mCurScene(nullptr)
	, mIsExitGame(false)
{

}
SceneManager& SceneManager::GetInstance()
{
	return _SceneManager;
}

SceneManager::~SceneManager()
{
	delete mCurScene;
}

bool SceneManager::RequestExitGame() const
{
	return mIsExitGame;
}

BaseScene* SceneManager::GetCurrentScene() const
{
	return mCurScene;
}

void SceneManager::Run()
{
	// 씬의 변경이 있다면 변경하고 , Update합니다. 
	if (mCurScene->IsDestroyScene() == true)
	{
		// 새로운 씬으로 변경
		BaseScene* nextScene = mCurScene->mNextScene;
		delete mCurScene;
		mCurScene = nextScene;
	}
	mIsExitGame = !(mCurScene->Update());
}

void SceneManager::LoadScene(BaseScene* scene)
{
	mCurScene->GoNextScene(scene);
	return;
}