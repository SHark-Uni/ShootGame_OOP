#pragma once

#include "GameBaseObject.h"


namespace ShootingGame
{
	class Enemy : public GameBaseObject
	{
	public:
		Enemy(int x, int y, int movingPattern, int enemyType);
		virtual ~Enemy();

		void Move();
		void Attack();
		//피격당함
		void Attacked(int damage);

		void Update() override;
		void Draw() override;
		
		void OnCollision(GameBaseObject* object) override;
	private:
		int mEnemyType;
		int mHp;
		int mMovingPattern;
		int mMoveCursor;

		int mEnemyInterval;
		int mEnemyTick;

		int mAttackPower;
	};
}