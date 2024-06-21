#include "FrameManager.h"

using namespace ShootingGame;

FrameManager FrameManager::_FrameManager;

FrameManager::FrameManager(unsigned int frame)
	:mFRAME_PER_SECONDS(0)
	,mMS_PER_FRAME(0)
{

}

FrameManager& FrameManager::GetInstance()
{
	return _FrameManager;
}

void FrameManager::SetFrame(unsigned int frame)
{
	mFRAME_PER_SECONDS = frame;
	mMS_PER_FRAME = 1000 / frame;
}

FrameManager::~FrameManager()
{

}

const unsigned int FrameManager::GetFrame() const
{
	return mFRAME_PER_SECONDS;
}

const unsigned int FrameManager::Get_MS_PER_FRAME() const
{
	return mMS_PER_FRAME;
}

DWORD FrameManager::GetMilliSeconds() const
{
	return timeGetTime();
}