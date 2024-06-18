#include <cassert>
#include <windows.h>

#include "Player.h"
#include "ScreenBuffer.h"
#include "GameObjectManager.h"
#include "TypeId.h"

using namespace ShootingGame;

Player::Player(playerInfo_t playerInfo)
	:GameBaseObject(static_cast<int>(ETypeId::PLAYER), playerInfo.x, playerInfo.y)
	,mHp(playerInfo.hp)
	,mAttackPower(playerInfo.atk)
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
		if (mX < MAX_SCREEN_WIDTH - 1)
		{
			++mX;
		}
		break;
	case VK_DOWN:
		if (mY < MAX_SCREEN_HEIGHT)
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
	GameObjectManager 
}


void Player::KeyInput()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		Move(VK_LEFT);
		return;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		Move(VK_RIGHT);
		return;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		Move(VK_DOWN);
		return;
	}

	if (GetAsyncKeyState(VK_UP))
	{
		Move(VK_UP);
		return;
	}
	// 공격 키 
	if (GetAsyncKeyState('Z'))
	{
		Attack();
		return;
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

}

void Player::Destroy()
{
	
}