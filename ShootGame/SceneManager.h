#pragma once
#include "BaseScene.h"

namespace ShootingGame
{
	class SceneManager
	{
	public:
		static SceneManager& GetInstance();

		BaseScene* GetCurrentScene() const;
		bool RequestExitGame() const;
		
		void Run();
		void LoadScene(BaseScene* NextScene);
	private:
		SceneManager();
		~SceneManager();

		SceneManager(const SceneManager& other) = delete;
		SceneManager(SceneManager&& other) = delete;

		SceneManager& operator=(const SceneManager& rhs) = delete;
		SceneManager& operator=(SceneManager&& rhs) = delete;

		bool mIsExitGame;
		static SceneManager _SceneManager;
		BaseScene* mCurScene;
	};
}