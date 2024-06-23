#pragma once

#include "BaseScene.h"

namespace ShootingGame
{
	class GameScene : public BaseScene
	{
	public:
		GameScene(unsigned int stageNumber);
		~GameScene();

		bool CanProceedToNextStage();
		bool CheckPlayerDead();

		bool Update() override;
	private:
		unsigned int mtotalStage;
		unsigned int mCurStage;
		unsigned int mtotalEnemy;
	};
}
