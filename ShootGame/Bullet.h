#pragma once

#include "GameBaseObject.h"

namespace ShootingGame
{
	class Bullet : public GameBaseObject
	{
	public:
		Bullet(int x, int y);
		virtual ~Bullet();

		void Move();

		void Update() override;
		void Draw() override;

		void OnCollision(GameBaseObject* object) override;
		void Destroy() override;
	private:
		unsigned int mBulltOwner;
		unsigned int mSpeed;
	};
}