#pragma once
#include "BaseScene.h"

namespace ShootingGame
{
	class LoadScene : public BaseScene
	{
	public:
		LoadScene(unsigned int curStage);
		~LoadScene();
		bool Update() override;
	private:
		unsigned int mCurStage;
	};
}

