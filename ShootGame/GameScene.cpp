#include "GameScene.h"
#include "ScreenBuffer.h"
#include "AssetLoaderManager.h"
#include "GameObjectManager.h"
#include "Enemy.h"
#include "Player.h"

#include "FileLoader.h"

using namespace ShootingGame;

GameScene::GameScene(unsigned int stageNumber)
	:mCurStage(stageNumber)
{
	AssetLoaderManager& am = AssetLoaderManager::GetInstance();
	GameObjectManager& gm = GameObjectManager::GetInstance();

	//�� �κ��� ���� �ȵ�µ�.. �� 
	FileLoader* curLoader = reinterpret_cast<FileLoader*>(am.GetLoader());
	FileLoader::StageInfo_t stageInfo = curLoader->GetStageInfo(stageNumber);

	mtotalStage = curLoader->GetTotalStageCount();
	mtotalEnemy = stageInfo.enemyCount;

	// �������� ���� ���Ӱ� �÷��̾� ����
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

bool GameScene::CanProceedToNextStage()
{

}

bool GameScene::CheckPlayerDead()
{
	// �̰� GameObjectManager���� ��Ź�ؾ��ϳ�?
	// PlayerId�� �ٵ� GameObject Manager�� �𸣴µ�?
	// Player�� �Ҹ��ڿ��� ���� ��ȯ���ش� ? 
		// �ϸ��ִ� ��������, ���� ���Ӿ����� �Ѿ ����, Player��ü�� �Ҹ��. GameObject�� �� ���ϱ�. 
		// �ٵ�, Player��ü�� ������ ���ص��Ǳ���.
		// �׷���, �Ź� GameScene�� �����ϴ°� �ƴ϶�, GameScene -> LOAD �̷� �������� �ұ�? NEXT STAGE LOAD��°� ���� ����
		// Stage Load������ ���Ӱ� �����ϸ� �Ǳ���.
		// �ٵ�, ��¶�� ��� ���� �Ҹ��ߴ��� ���ߴ��� Ȯ���� �ؾ��ؼ�.. GameObjectList�� �����ϱ��ϳ�.. 
		// �ƴϸ�, Enemy�� �Ҹ��ڿ��� GameScene�� Total Enemy�� 1���� ���ش�? �װ͵� �ϸ��ֱ���. ���� ������� ���� GameScene���״ϱ�.

}

//�� ��ȯ��, ���� �Ҹ��ڰ� �Ҹ�.
GameScene::~GameScene()
{
	//GameObject�� �� ��������.
	GameObjectManager::GetInstance().DestroyAllObject();
}

bool GameScene::Update()
{
	// �÷��� �� , �÷��̾ �׾����� Ȯ�� �ؾ���

	
	
	// ���� �������� �������� Check
	if (CanProceedToNextStage)
	{
		// ���� ���������� ������ �����������, Ŭ���� ������ ������.
	}
	

	

}