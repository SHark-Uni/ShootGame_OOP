#include "Enemy.h"
#include "TypeId.h"
#include "EnemyTypeId.h"
#include "SceneTypeId.h"

#include "GameObjectManager.h"
#include "AssetLoaderManager.h"
#include "FrameManager.h"

#include "FileLoader.h"
#include "SceneManager.h"
#include "GameScene.h"

#include "ScreenBuffer.h"
#include "Bullet.h"

using namespace ShootingGame;

Enemy::Enemy(int x, int y, int movingPattern, int enemyType)
	: GameBaseObject(static_cast<int>(eTypeId::ENEMY), x, y)
	, mMovingPattern(movingPattern)
	, mEnemyType(enemyType)
	, mHp(0)
	, mEnemyInterval(0)
	, mAttackPower(0)
	, mMoveCursor(0)
	, mEnemyTick(0)
{
	//유형별로 Spawn시키기
	switch (enemyType)
	{
	case static_cast<int>(eEnemyTypeId::NORMAL):
		mHp = static_cast<int>(eNormalTypeInfo::HP);
		mEnemyInterval = static_cast<int>(eNormalTypeInfo::Interval);
		mAttackPower = static_cast<int>(eNormalTypeInfo::AttackPower);
		break;
	case static_cast<int>(eEnemyTypeId::ATTACKER):
		mHp = static_cast<int>(eAttackTypeInfo::HP);
		mEnemyInterval = static_cast<int>(eAttackTypeInfo::Interval);
		mAttackPower = static_cast<int>(eAttackTypeInfo::AttackPower);
		break;
	case static_cast<int>(eEnemyTypeId::DEFENDER):
		mHp = static_cast<int>(eDefenderTypeInfo::HP);
		mEnemyInterval = static_cast<int>(eDefenderTypeInfo::Interval);
		mAttackPower = static_cast<int>(eDefenderTypeInfo::AttackPower);
		break;
	default:
		assert(false);
		break;
	}
}

//무빙 패턴에 따라 움직여야함.
void Enemy::Move()
{
	AssetLoaderManager& al = AssetLoaderManager::GetInstance();
	FileLoader* movePattern = reinterpret_cast<FileLoader*>(al.GetLoader());
	FileLoader::PatternInfo_t pattern = movePattern->PatternInfo(mMovingPattern);
		
	mX += pattern.patterns[mMoveCursor].x;
	mY += pattern.patterns[mMoveCursor].y;

	mMoveCursor = (mMoveCursor + 1) % pattern.patternCount;
}

//Create Bullet
void Enemy::Attack()
{
	GameObjectManager& gm = GameObjectManager::GetInstance();
	gm.CreateObject(new Bullet(mX, mY + 1, static_cast<int>(eTypeId::ENEMY), mAttackPower, mEnemyInterval));
}

void Enemy::Update()
{
	//공격 후 , 움직이기
	++mEnemyTick;
	if (mEnemyInterval == mEnemyTick)
	{
		Attack();
		Move();
		mEnemyTick = 0;
	}

}

void Enemy::Draw()
{
	ScreenBuffer& s = ScreenBuffer::GetInstance();

	switch (mEnemyType)
	{
	case static_cast<int>(eEnemyTypeId::NORMAL):
		s.DrawSprite(mX, mY, L'E');
		break;
	case static_cast<int>(eEnemyTypeId::ATTACKER):
		s.DrawSprite(mX, mY, L'A');
		break;
	case static_cast<int>(eEnemyTypeId::DEFENDER):
		s.DrawSprite(mX, mY, L'D');
		break;
	default:
		break;
	}

}

void Enemy::OnCollision(GameBaseObject* object)
{

}

void Enemy::Attacked(int damage)
{
	mHp -= damage;

	if (mHp < 0)
	{
		mIsAlive = false;
	}
	return;
}


Enemy::~Enemy()
{
	// 게임 씬에서 적이 소멸한다.
	SceneManager& sm = SceneManager::GetInstance();
	
	GameScene* gameScene = reinterpret_cast<GameScene*>(sm.GetCurrentScene());
	gameScene->OnEnemyDead();
}