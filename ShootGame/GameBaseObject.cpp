#include "GameBaseObject.h"

using namespace ShootingGame;

GameBaseObject::GameBaseObject(int typeId, int x, int y)
	:mTypeId(typeId)
	, mX(x)
	, mY(y)
	, mIsAlive(true)
{

}

const int GameBaseObject::GetTypeId() const
{
	return mTypeId;
}

const int GameBaseObject::GetX() const
{
	return mX;
}
const int GameBaseObject::GetY() const
{
	return mY;
}

GameBaseObject::~GameBaseObject()
{
	
}