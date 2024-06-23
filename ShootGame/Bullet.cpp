#include "Bullet.h"
#include "TypeId.h"
#include "ScreenBuffer.h"

using namespace ShootingGame;


Bullet::Bullet(int x, int y, int BulletOwner, int speed)
	:GameBaseObject(static_cast<int>(ETypeId::BULLET), x, y)
	,mBulltOwner(BulletOwner)
	,mSpeed(speed)
{

}

Bullet::~Bullet()
{

}

void Bullet::Move()
{
	if (mBulltOwner == static_cast<int>(ETypeId::PLAYER))
	{
		//OutOfRange
		if (mY <= 0)
		{
			mIsAlive = false;
			return;
		}
		--mY;
	}

	else if (mBulltOwner == static_cast<int>(ETypeId::ENEMY))
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
	if ((object->GetX() == mX) && (object->GetY() == mY))
	{
		mIsAlive = false;
	}
	return;
}
