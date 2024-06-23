#pragma once

#include "GameBaseObject.h"
#include "IPlayable.h"

namespace ShootingGame
{
	class Player : public GameBaseObject, public IPlayable
	{
	public:
		Player(int x, int y);
		~Player();
		void Move(const int keyinput);
		void Attack();
		void Attacked(int damage);

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