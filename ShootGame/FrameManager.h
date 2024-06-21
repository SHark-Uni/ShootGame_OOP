#pragma once

#include <windows.h>

namespace ShootingGame
{
	class FrameManager
	{
	public:
		static FrameManager& GetInstance();
		
		const unsigned int GetFrame() const;
		const unsigned int Get_MS_PER_FRAME() const;
		void SetFrame(unsigned int frame);

		DWORD GetMilliSeconds() const;
	private:
		FrameManager();
		~FrameManager();

		FrameManager(const FrameManager& other) = delete;
		FrameManager(FrameManager&& other) = delete;
		FrameManager& operator=(const FrameManager& rhs) = delete;
		FrameManager& operator=(FrameManager&& rhs) = delete;

		static FrameManager _FrameManager;
		unsigned int mFRAME_PER_SECONDS;
		unsigned int mMS_PER_FRAME;
	};
}
