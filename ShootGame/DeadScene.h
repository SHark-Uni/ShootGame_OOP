#pragma once

#include "BaseScene.h"

namespace ShootingGame
{
	class DeadScene : public BaseScene
	{
	public:
		explicit DeadScene(unsigned int curStage);
		~DeadScene();
		void DrawDeadScreen();
		bool Update() override;
	private:
		enum {
			RETRY_MENU = 10,
			TITLE_MENU = 12,
			EXIT_MENU = 14,
			MENU_CURSOR_X = 15,
		};
		unsigned int mDeadStage;
	};
}