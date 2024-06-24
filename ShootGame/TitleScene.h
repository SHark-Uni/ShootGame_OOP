#pragma once
#include "BaseScene.h"

namespace ShootingGame
{
	class TitleScene : public BaseScene
	{
	public:
		TitleScene();
		~TitleScene();
		
		void DrawMainMenu();
		bool Update() override;
	private:
		enum {
			START_MENU_CURSOR_Y = 15,
			EXIT_MENU_CURSOR_Y = 16,
			MENU_CURSOR_X = 25,
		};
		int mMenuCursorX;
		int mMenuCursorY;
	};
}
