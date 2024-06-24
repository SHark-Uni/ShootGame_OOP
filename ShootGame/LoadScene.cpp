#include "LoadScene.h"
#include "SceneManager.h"
#include "AssetLoaderManager.h"
#include "FileLoader.h"

#include "GameScene.h"

#include "SceneTypeId.h"

using namespace ShootingGame;

LoadScene::LoadScene(unsigned int curStage)
	:BaseScene(static_cast<int>(eSceneTypeId::LOAD_SCENE))
	,mCurStage(curStage)
{

}

LoadScene::~LoadScene()
{

}

bool LoadScene::Update()
{
	//다음 스테이지로 로딩
	SceneManager& sm = SceneManager::GetInstance();

	AssetLoaderManager& am = AssetLoaderManager::GetInstance();

	FileLoader* curLoader = reinterpret_cast<FileLoader*>(am.GetLoader());
	FileLoader::StageInfo_t stageInfo = curLoader->GetStageInfo(mCurStage);

	unsigned int totalStage = curLoader->GetTotalStageCount();
	unsigned int totalEnemy = stageInfo.enemyCount;

	sm.LoadScene(new GameScene(totalStage, mCurStage, totalEnemy));

	return true;
}