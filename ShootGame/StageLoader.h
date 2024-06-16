#pragma once

#include "IAssetLoader.h"
#include <windows.h>

namespace ShootingGame
{
	class StageLoader : public IAssetLoader
	{
	public:
		typedef struct stageInfo
		{
			int x;
			int y;
			int movingPattern;
		} stageInfo_t;

		StageLoader(const wchar_t* fileName);
		void LoadStageMetaFile();
		void LoadStageDetailFile();

		const stageInfo_t& GetStageInfo() const;

		void Load();
		virtual ~StageLoader();
	private:
		WCHAR* mFileName;

		unsigned int mStageCount;
		stageInfo_t* mStageInfo;
	};
}