#pragma once

#include "GameBaseObject.h"
#include "IPlayable.h"

namespace ShootingGame
{
	class Player : public GameBaseObject, public IPlayable
	{
	public:
		typedef struct player
		{
			int x;
			int y;

			int atk;
			int attackSpeed;

			int hp;
			int speed;
		}playerInfo_t;

		Player(playerInfo_t playerInfo);
		~Player();
		void Move(const int keyinput);
		void Attack();

		void KeyInput() override;
		void Update() override;
		void Draw() override;

		void OnCollision(GameBaseObject* object) override;
	private:
		int mHp;
		int mSpeed;

		int mAttackPower;
		int mAttackSpeed;
	};
}