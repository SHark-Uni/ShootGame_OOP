#pragma once

namespace ShootingGame
{
	class BaseScene
	{
		friend class SceneManager;
	public:
		BaseScene(int scenetype);
		virtual ~BaseScene();

		void GoNextScene(BaseScene* nextScene);
		int GetSceneTypeId() const;
		bool IsDestroyScene();


		virtual bool Update() = 0;
	protected:
		int mSceneType;
		BaseScene* mNextScene;
	};
}
