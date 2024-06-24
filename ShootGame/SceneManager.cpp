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
	// ���� ������ �ִٸ� �����ϰ� , Update�մϴ�. 
	if (mCurScene->IsDestroyScene() == true)
	{
		// ���ο� ������ ����
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