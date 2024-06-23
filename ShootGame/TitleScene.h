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
			START_MENU_CURSOR = 15,
			EXIT_MENU_CURSOR = 16,
		};
		int mMenuCursorX;
		int mMenuCursorY;
	};
}
