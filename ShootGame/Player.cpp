#include <cassert>
#include <windows.h>

#include "Player.h"
#include "Bullet.h"
#include "ScreenBuffer.h"
#include "GameObjectManager.h"
#include "TypeId.h"

using namespace ShootingGame;

Player::Player(int x, int y)
	:GameBaseObject(static_cast<int>(eTypeId::PLAYER), x, y)
	,mHp(10)
	,mAttackPower(3)
	,mAttackSpeed(20)
	,mSpeed(20)
{

}

Player::~Player()
{

}

void Player::Move(const int keyinput)
{
	switch (keyinput)
	{
	case VK_LEFT:
		if (mX > 0)
		{
			--mX;
		}
		break;
	case VK_RIGHT:
		if (mX < MAX_MOVABLE_WIDTH_INDEX)
		{
			++mX;
		}
		break;
	case VK_DOWN:
		if (mY < MAX_MOVABLE_HEIGHT_INDEX)
		{
			++mY;
		}
		break;
	case VK_UP:
		if (mY > 0)
		{
			--mY;
		}
		break;
	default:
		assert(false);
		break;
	}
}

void Player::Attack()
{
	GameObjectManager& gm = GameObjectManager::GetInstance();
	gm.CreateObject(new Bullet(mX, mY - 1, static_cast<int>(eTypeId::PLAYER), mAttackPower, mAttackSpeed));
}

void Player::Attacked(int damage)
{
	mHp -= damage;
	if (mHp < 0)
	{
		mIsAlive = false;
	}
	return;
}

void Player::KeyInput()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		Move(VK_LEFT);
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		Move(VK_RIGHT);
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		Move(VK_DOWN);
	}

	if (GetAsyncKeyState(VK_UP))
	{
		Move(VK_UP);
	}
	// °ø°Ý Å° 
	if (GetAsyncKeyState('Z'))
	{
		Attack();
	}
}


void Player::Draw()
{
	ScreenBuffer& s = ScreenBuffer::GetInstance();

	s.DrawSprite(mX, mY, L'P');

	s.DrawSprite(0, 23, L'H');
	s.DrawSprite(1, 23, L'P');
	s.DrawSprite(2, 23, L'0' + mHp);
}

void Player::Update()
{
	KeyInput();
}


void Player::OnCollision(GameBaseObject* object)
{
	return;
}
