#include "Enemy.h"
#include "TypeId.h"
#include "EnemyTypeId.h"
#include "SceneTypeId.h"

#include "GameObjectManager.h"
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
	, mSpeed(0)
	, mAttackPower(0)
	, mAttackSpeed(0)
{
	//유형별로 Spawn시키기
	switch (enemyType)
	{
	case static_cast<int>(eEnemyTypeId::NORMAL):
		mHp = static_cast<int>(eNormalTypeInfo::HP);
		mSpeed = static_cast<int>(eNormalTypeInfo::Speed);

		mAttackPower = static_cast<int>(eNormalTypeInfo::AttackPower);
		mAttackSpeed = static_cast<int>(eNormalTypeInfo::AttackSpeed);
		break;
	case static_cast<int>(eEnemyTypeId::ATTACKER):
		mHp = static_cast<int>(eAttackTypeInfo::HP);
		mSpeed = static_cast<int>(eAttackTypeInfo::Speed);

		mAttackPower = static_cast<int>(eAttackTypeInfo::AttackPower);
		mAttackSpeed = static_cast<int>(eAttackTypeInfo::AttackSpeed);
		break;
	case static_cast<int>(eEnemyTypeId::DEFENDER):
		mHp = static_cast<int>(eDefenderTypeInfo::HP);
		mSpeed = static_cast<int>(eDefenderTypeInfo::Speed);

		mAttackPower = static_cast<int>(eDefenderTypeInfo::AttackPower);
		mAttackSpeed = static_cast<int>(eDefenderTypeInfo::AttackSpeed);
		break;
	default:
		assert(false);
		break;
	}
}

//무빙 패턴에 따라 움직여야함.
void Enemy::Move()
{
	//TEST Move
	++mX;
}

//Create Bullet
void Enemy::Attack()
{
	GameObjectManager& gm = GameObjectManager::GetInstance();

	gm.CreateObject(new Bullet(mX, mY + 1, static_cast<int>(eTypeId::ENEMY), mAttackPower, mAttackSpeed));
}

void Enemy::Update()
{
	//공격 후 , 움직이기
	Attack();
	Move();
}

void Enemy::Draw()
{
	ScreenBuffer& s = ScreenBuffer::GetInstance();

	s.DrawSprite(mX, mY, L'E');
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