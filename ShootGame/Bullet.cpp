#include "Bullet.h"
#include "TypeId.h"
#include "Enemy.h"
#include "Player.h"
#include "ScreenBuffer.h"

using namespace ShootingGame;


Bullet::Bullet(int x, int y, int BulletOwner, int mBulletDamage, int speed)
	:GameBaseObject(static_cast<int>(eTypeId::BULLET), x, y)
	,mBulletOwner(BulletOwner)
	,mSpeed(speed)
{

}

Bullet::~Bullet()
{

}

void Bullet::Move()
{
	if (mBulletOwner == static_cast<int>(eTypeId::PLAYER))
	{
		//OutOfRange
		if (mY <= 0)
		{
			mIsAlive = false;
			return;
		}
		--mY;
	}

	else if (mBulletOwner == static_cast<int>(eTypeId::ENEMY))
	{
		//OutOfRange
		if (mY >= MAX_SCREEN_HEIGHT)
		{
			mIsAlive = false;
			return;

		}
		++mY;
	}
	return;
}

void Bullet::Draw()
{
	ScreenBuffer& s = ScreenBuffer::GetInstance();

	s.DrawSprite(mX, mY, L'*');
}

void Bullet::Update()
{
	Move();
}

void Bullet::OnCollision(GameBaseObject* object)
{
	int objectType = object->GetTypeId();
	
	if ((object->GetX() == mX) && (object->GetY() == mY))
	{
		// �÷��̾� �Ѿ˰� ���� �ε����� ���
		if (mBulletOwner == static_cast<int>(eTypeId::PLAYER) && (objectType == static_cast<int>(eTypeId::ENEMY)))
		{
			Enemy* enemy = reinterpret_cast<Enemy*>(object);
			enemy->Attacked(mBulletDamage);

			// �Ѿ� ��������ϱ�
			mIsAlive = false;
			return;
		}
		// �� �Ѿ˿� Player�� �ε����� ���
		if (mBulletOwner == static_cast<int>(eTypeId::ENEMY) && (objectType == static_cast<int>(eTypeId::PLAYER)))
		{
			Player* player = reinterpret_cast<Player*>(object);
			player->Attacked(mBulletDamage);

			mIsAlive = false;
		}
	}
	return;
}
