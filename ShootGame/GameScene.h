#pragma once
#include "BaseScene.h"

namespace ShootingGame
{
	class GameScene : public BaseScene
	{
	public:
		GameScene();
		explicit GameScene(unsigned int curStage);
		GameScene(unsigned int totalStage, unsigned int curStage, unsigned int totalEnemy);

		~GameScene();

		void OnEnemyDead();
		void OnPlayerDead();

		bool Update() override;
	private:
		bool mIsPlayerAlive;
		unsigned int mtotalStage;
		unsigned int mCurStage;

		unsigned int mtotalEnemy;
		unsigned int mCurEnemy;
	};
}
