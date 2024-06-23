#include "BaseScene.h"

using namespace ShootingGame;

BaseScene::BaseScene()
	:mNextScene(nullptr)
{

}

BaseScene::~BaseScene()
{
	
}
void BaseScene::GoNextScene(BaseScene* nextScene)
{
	mNextScene = nextScene;
}

bool BaseScene::IsDestroyScene()
{
	return (mNextScene != nullptr)
}