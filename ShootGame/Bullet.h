#pragma once

#include "GameBaseObject.h"

namespace ShootingGame
{
	class Bullet : public GameBaseObject
	{
	public:
		Bullet(int x, int y, int BulletOwner, int mBulletDamage, int speed);
		virtual ~Bullet();

		void Move();

		void Update() override;
		void Draw() override;
		void OnCollision(GameBaseObject* object) override;

	private:
		int mBulletDamage;
		int mBulletOwner;
		int mSpeed;
	};
}