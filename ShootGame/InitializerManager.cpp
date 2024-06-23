#include "InitializerManager.h"

using namespace ShootingGame;

InitializerManager InitializerManager::_Initalizer;

InitializerManager::InitializerManager()
	:mInit(nullptr)
{
	
}

InitializerManager& InitializerManager::GetInstance()
{
	return _Initalizer;
}

void InitializerManager::CreateInitializer(GameInitiallizer* init)
{
	mInit = init;
}

void InitializerManager::Init()
{
	mInit->Init();
}

InitializerManager::~InitializerManager()
{
	delete mInit;
}