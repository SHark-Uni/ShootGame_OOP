#include <cassert>
#include <windows.h>

#include "Player.h"
#include "Bullet.h"
#include "ScreenBuffer.h"
#include "GameObjectManager.h"
#include "TypeId.h"

using namespace ShootingGame;

Player::Player(playerInfo_t playerInfo)
	:GameBaseObject(static_cast<int>(ETypeId::PLAYER), playerInfo.x, playerInfo.y)
	,mHp(playerInfo.hp)
	,mAttackPower(playerInfo.atk)
	,mAttackSpeed(playerInfo.attackSpeed)
	,mSpeed(playerInfo.speed)
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

	gm.CreateObject(new Bullet(mX, mY - 1, static_cast<int>(ETypeId::PLAYER), mAttackSpeed));
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
	// 공격 키 
	if (GetAsyncKeyState('Z'))
	{
		Attack();
	}
}


void Player::Draw()
{
	ScreenBuffer& s = ScreenBuffer::GetInstance();

	s.SpriteDraw(mX, mY, L'P');

	s.SpriteDraw(0, 23, L'H');
	s.SpriteDraw(1, 23, L'P');
	s.SpriteDraw(2, 23, L'0' + mHp);
}

void Player::Update()
{
	//키입력
	KeyInput();
	//렌더링
	Draw();
}


void Player::OnCollision(GameBaseObject* object)
{
	if ((object->GetX() == mX) && (object->GetY() == mY))
	{
		mIsAlive = false;
	}
	return;
}
