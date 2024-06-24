#include "LoadScene.h"
#include "GameScene.h"
#include <iostream>

#include "SceneManager.h"
#include "AssetLoaderManager.h"
#include "GameObjectManager.h"
#include "Enemy.h"
#include "FileLoader.h"

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
	//���� ���������� �ε�
	SceneManager& sm = SceneManager::GetInstance();

	AssetLoaderManager& am = AssetLoaderManager::GetInstance();
	GameObjectManager& gm = GameObjectManager::GetInstance();
	FileLoader* curLoader = reinterpret_cast<FileLoader*>(am.GetLoader());
	FileLoader::StageInfo_t stageInfo = curLoader->GetStageInfo(mCurStage);

	unsigned int totalStage = curLoader->GetTotalStageCount();
	unsigned int totalEnemy = stageInfo.enemyCount;

	// �������� ������ �°� �� ����
	for (size_t i = 0; i < totalEnemy; i++)
	{
		gm.CreateObject(
			new Enemy(
				stageInfo.enemies[i].x,
				stageInfo.enemies[i].y,
				stageInfo.enemies[i].pattern,
				stageInfo.enemies[i].enemyType
			)
		);
	}

	sm.LoadScene(new GameScene(totalStage, mCurStage, totalEnemy));

	return true;
}