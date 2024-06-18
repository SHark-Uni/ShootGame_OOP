#include "GameBaseObject.h"

using namespace ShootingGame;

GameBaseObject::GameBaseObject(int typeId, int x, int y)
	:mTypeId(typeId)
	, mX(x)
	, mY(y)
	, mIsAlive(true)
{

}

GameBaseObject::~GameBaseObject()
{
	
}