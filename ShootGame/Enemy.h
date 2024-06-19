#pragma once

#include "GameBaseObject.h"


namespace ShootingGame
{
	class Enemy : public GameBaseObject
	{
		typedef struct EnemyInfo
		{
			int x;
			int y;

			int hp;
			int atk;
			int attackSpeed;

			int speed;
			int pattern;
		}EnemyInfo_t;

		Enemy(EnemyInfo_t enemyInfo);
		virtual ~Enemy();

		void Move();
		void Attack();

		void Update() override;
		void Draw() override;

		void OnCollision(GameBaseObject* object) override;
	private:
		int mMovingPattern;
		
		int mHp;
		int mSpeed;

		int mAttackPower;
		int mAttackSpeed;
	};
}