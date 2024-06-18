#pragma once

#include "GameBaseObject.h"

namespace ShootingGame
{
	class Enemy : public GameBaseObject
	{
		Enemy(int x, int y);

		void Move();
		void Attack();

		void Update() override;
		void Draw() override;

		void OnCollision(GameBaseObject* object) override;
		void Destroy() override;
	private:
		unsigned int mMovingPattern;
		unsigned int mSpeed;
		int mHp;
		int mAttackPower;
	};
}