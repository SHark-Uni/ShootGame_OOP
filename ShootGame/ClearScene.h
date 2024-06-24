#pragma once

#include "BaseScene.h"

namespace ShootingGame
{
	class ClearScene : public BaseScene
	{
	public:
		ClearScene();
		~ClearScene();
		void DrawClearScreen();
		bool Update() override;
	private:
		enum
		{
			TITLE_MENU = 10,
			MENU_CURSOR_X = 20,
		};
	};
}
