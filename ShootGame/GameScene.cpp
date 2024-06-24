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
	// �÷��̾� ����
	gm.CreateObject(new Player((MAX_SCREEN_WIDTH - 1) / 2, 0));
	// �������� ������ �°� �� ����
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
//����� ��, ����Ǵ� �Լ�
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
	// �÷��̾� ����
	gm.CreateObject(new Player((MAX_SCREEN_WIDTH - 1) / 2, 0));
	// �������� ������ �°� �� ����
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

//���� �ε� ��, �ʿ��� ������
GameScene::GameScene(unsigned int totalStage, unsigned int curStage, unsigned int totalEnemy)
	: BaseScene(static_cast<int>(eSceneTypeId::GAME_SCENE))
	, mtotalStage(totalStage)
	, mCurStage(curStage)
	, mtotalEnemy(totalEnemy)
	, mCurEnemy(totalEnemy)
	, mIsPlayerAlive(true)
{
}

// �̰� GameObjectManager���� ��Ź�ؾ��ϳ�?
// PlayerId�� �ٵ� GameObject Manager�� �𸣴µ�?
// Player�� �Ҹ��ڿ��� ���� ��ȯ���ش� ? 
	// �ϸ��ִ� ��������, ���� ���Ӿ����� �Ѿ ����, Player��ü�� �Ҹ��. GameObject�� �� ���ϱ�. 
	// �ٵ�, Player��ü�� ������ ���ص��Ǳ���.
	// �׷���, �Ź� GameScene�� �����ϴ°� �ƴ϶�, GameScene -> LOAD �̷� �������� �ұ�? NEXT STAGE LOAD��°� ���� ����
	// Stage Load������ ���Ӱ� �����ϸ� �Ǳ���.
	// �ٵ�, ��¶�� ��� ���� �Ҹ��ߴ��� ���ߴ��� Ȯ���� �ؾ��ؼ�.. GameObjectList�� �����ϱ��ϳ�.. 
	// �ƴϸ�, Enemy�� �Ҹ��ڿ��� GameScene�� Total Enemy�� 1���� ���ش�? �װ͵� �ϸ��ֱ���. ���� ������� ���� GameScene���״ϱ�.

void GameScene::OnEnemyDead()
{
	--mCurEnemy;
}

void GameScene::OnPlayerDead()
{
	mIsPlayerAlive = false;
}

//�� ��ȯ��, ���� �Ҹ��ڰ� �Ҹ�.
GameScene::~GameScene()
{

}

bool GameScene::Update()
{
	SceneManager& sm = SceneManager::GetInstance();
	GameObjectManager& gm = GameObjectManager::GetInstance();
	// �÷��� �� , �÷��̾ �׾����� Ȯ�� �ؾ���
	if (mIsPlayerAlive == false)
	{
		// ������ GameObjec�� ��ü ���� + DeadScene���� �Ѿ��
		gm.DestroyAllObject();
		sm.LoadScene(new DeadScene(mCurStage));
		return true;
	}

	// ���� ���������� ������ �����������, Ŭ���� ������ ������.
	if (mCurEnemy == 0 && mCurStage == mtotalStage - 1)
	{
		//�÷��̾� ��ü �Ҹ� + ClearScene���� �̵�
		gm.DestroyAllObject();
		sm.LoadScene(new ClearScene());
		return true;
	}
	// ��� ���� �׾��ٸ� , ���� ������ �Ѿ���Ѵ�.
	if (mCurEnemy == 0)
	{
		sm.LoadScene(new LoadScene(++mCurStage));
		return true;
	}
	return true;
}