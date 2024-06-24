#include <cassert>
#include <windows.h>

#include "Player.h"
#include "Bullet.h"
#include "ScreenBuffer.h"
#include "GameObjectManager.h"
#include "SceneManager.h"
#include "GameScene.h"

#include "TypeId.h"
#include "SceneTypeId.h"

using namespace ShootingGame;

Player::Player(int x, int y)
	:GameBaseObject(static_cast<int>(eTypeId::PLAYER), x, y)
	, mHp(8)
	, mAttackPower(3)
	, mPlayerInterval(2)
	, mPlayerTick(0)
{

}

Player::~Player()
{
	SceneManager& sm = SceneManager::GetInstance();
	// 게임 중 사망하는 경우
	if (sm.GetCurrentScene()->GetSceneTypeId() == static_cast<int>(eSceneTypeId::GAME_SCENE))
	{
		GameScene* gameScene = reinterpret_cast<GameScene*>(sm.GetCurrentScene());
		gameScene->OnPlayerDead();
	}

	//게임이 끝나서 플레이어 개체를 소멸시키는 경우
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
	gm.CreateObject(new Bullet(mX, mY - 1, static_cast<int>(eTypeId::PLAYER), mAttackPower, mPlayerInterval));
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
	// 공격 키 
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

	s.DrawSprite(2, 23, L'8');
	s.DrawSprite(3, 23, L'/');
	s.DrawSprite(4, 23, L'0' + mHp);
}

void Player::Update()
{
	++mPlayerTick;
	if (mPlayerTick == mPlayerInterval)
	{
		KeyInput();
		mPlayerTick = 0;
	}
}


void Player::OnCollision(GameBaseObject* object)
{
	return;
}
