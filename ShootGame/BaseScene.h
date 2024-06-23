#pragma once

namespace ShootingGame
{
	class BaseScene
	{
		friend class SceneManager;
	public:
		BaseScene();
		virtual ~BaseScene();

		void GoNextScene(BaseScene* nextScene);
		bool IsDestroyScene();

		virtual bool Update() = 0;
	protected:
		BaseScene* mNextScene;
	};
}
