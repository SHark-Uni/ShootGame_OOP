#include "GameScene.h"
#include "ScreenBuffer.h"

#include <iostream>

#include "ClearScene.h"
#include "LoadScene.h"
#include "DeadScene.h"

#include "SceneManager.h"
#include "AssetLoaderManager.h"
#include "GameObjectManager.h"

#include "Enemy.h"
#include "Player.h"

#include "FileLoader.h"
#include "SceneTypeId.h"

using namespace ShootingGame;

GameScene::GameScene()
	: BaseScene(static_cast<int>(eSceneTypeId::GAME_SCENE))
	, mCurStage(0)
	, mIsPlayerAlive(true)
{
	AssetLoaderManager& am = AssetLoaderManager::GetInstance();
	
	FileLoader* curLoader = reinterpret_cast<FileLoader*>(am.GetLoader());
	FileLoader::StageInfo_t stageInfo = curLoader->GetStageInfo(0);

	mtotalStage = curLoader->GetTotalStageCount();
	mCurStage = 0;

	mtotalEnemy = stageInfo.enemyCount;
	mCurEnemy = stageInfo.enemyCount;
	
	GameObjectManager& gm = GameObjectManager::GetInstance();
	// 플레이어 스폰
	gm.CreateObject(new Player((MAX_SCREEN_WIDTH - 1) / 2, 0));
	// 스테이지 정보에 맞게 적 스폰
	for (size_t i = 0; i < mtotalEnemy; i++)
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
}
//재시작 시, 실행되는 함수
GameScene::GameScene(unsigned int curStage)
	: BaseScene(static_cast<int>(eSceneTypeId::GAME_SCENE))
	, mCurStage(curStage)
	, mIsPlayerAlive(true)
{
	AssetLoaderManager& am = AssetLoaderManager::GetInstance();

	FileLoader* curLoader = reinterpret_cast<FileLoader*>(am.GetLoader());
	FileLoader::StageInfo_t stageInfo = curLoader->GetStageInfo(mCurStage);

	mtotalStage = curLoader->GetTotalStageCount();

	mtotalEnemy = stageInfo.enemyCount;
	mCurEnemy = stageInfo.enemyCount;

	GameObjectManager& gm = GameObjectManager::GetInstance();
	// 플레이어 스폰
	gm.CreateObject(new Player((MAX_SCREEN_WIDTH - 1) / 2, 0));
	// 스테이지 정보에 맞게 적 스폰
	for (size_t i = 0; i < mtotalEnemy; i++)
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
}

//게임 로딩 시, 필요한 생성자
GameScene::GameScene(unsigned int totalStage, unsigned int curStage, unsigned int totalEnemy)
	: BaseScene(static_cast<int>(eSceneTypeId::GAME_SCENE))
	, mtotalStage(totalStage)
	, mCurStage(curStage)
	, mtotalEnemy(totalEnemy)
	, mCurEnemy(totalEnemy)
	, mIsPlayerAlive(true)
{
}

// 이거 GameObjectManager한테 부탁해야하나?
// PlayerId를 근데 GameObject Manager는 모르는데?
// Player의 소멸자에서 씬을 전환해준다 ? 
	// 일리있는 말이지만, 다음 게임씬으로 넘어갈 때도, Player개체가 소멸됨. GameObject를 다 비우니까. 
	// 근데, Player개체는 삭제를 안해도되긴함.
	// 그러면, 매번 GameScene을 생성하는게 아니라, GameScene -> LOAD 이런 과정으로 할까? NEXT STAGE LOAD라는걸 따로 만들어서
	// Stage Load과정을 새롭게 구현하면 되긴함.
	// 근데, 어쨋뜬 모든 적이 소멸했는지 안했는지 확인은 해야해서.. GameObjectList를 얻어야하긴하네.. 
	// 아니면, Enemy의 소멸자에서 GameScene의 Total Enemy를 1개씩 없앤다? 그것도 일리있긴함. 적이 사라지는 씬은 GameScene일테니까.

void GameScene::OnEnemyDead()
{
	--mCurEnemy;
}

void GameScene::OnPlayerDead()
{
	mIsPlayerAlive = false;
}

//씬 전환시, 씬의 소멸자가 불림.
GameScene::~GameScene()
{

}

bool GameScene::Update()
{
	SceneManager& sm = SceneManager::GetInstance();
	GameObjectManager& gm = GameObjectManager::GetInstance();
	// 플레이 중 , 플레이어가 죽었는지 확인 해야함
	if (mIsPlayerAlive == false)
	{
		// 나머지 GameObjec의 개체 정리 + DeadScene으로 넘어가기
		gm.DestroyAllObject();
		sm.LoadScene(new DeadScene(mCurStage));
		return true;
	}

	// 현재 스테이지가 마지막 스테이지라면, 클리어 씬으로 가야함.
	if (mCurEnemy == 0 && mCurStage == mtotalStage - 1)
	{
		//플레이어 개체 소멸 + ClearScene으로 이동
		gm.DestroyAllObject();
		sm.LoadScene(new ClearScene());
		return true;
	}
	// 모든 적이 죽었다면 , 다음 씬으로 넘어가야한다.
	if (mCurEnemy == 0)
	{
		sm.LoadScene(new LoadScene(++mCurStage));
		return true;
	}
	return true;
}