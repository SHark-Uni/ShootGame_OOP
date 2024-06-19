#include "Enemy.h"
#include "TypeId.h"
#include "GameObjectManager.h"
#include "ScreenBuffer.h"
#include "Bullet.h"

using namespace ShootingGame;

Enemy::Enemy(EnemyInfo_t enemyInfo)
	:GameBaseObject(static_cast<int>(ETypeId::ENEMY), enemyInfo.x, enemyInfo.y)
	,mHp(enemyInfo.hp)
	,mAttackPower(enemyInfo.atk)
	,mAttackSpeed(enemyInfo.attackSpeed)
	,mSpeed(enemyInfo.speed)
	,mMovingPattern(enemyInfo.pattern)
{

}

//���� ���Ͽ� ���� ����������.
void Enemy::Move()
{

}

//Create Bullet
void Enemy::Attack()
{
	GameObjectManager& gm = GameObjectManager::GetInstance();

	gm.CreateObject(new Bullet(mX, mY + 1, static_cast<int>(ETypeId::ENEMY), mAttackSpeed));
}

void Enemy::Update()
{
	//Move
	
}

void Enemy::Draw()
{
	ScreenBuffer& s = ScreenBuffer::GetInstance();

	s.SpriteDraw(mX, mY, L'E');
}

void Enemy::OnCollision(GameBaseObject* object)
{
	mIsAlive = false;
}



Enemy::~Enemy()
{

}