#pragma once

#include <windows.h>
#include "BaseAssetLoader.h"

namespace ShootingGame
{
	class FileLoader : public BaseAssetLoader
	{
	public:
		FileLoader();
		virtual ~FileLoader();

		typedef struct pos
		{
			int x;
			int y;
		}pos_t;
		
		typedef struct pattern
		{
			int patternCount;
			pos_t* patterns;
		}PatternInfo_t;
		
		typedef struct enemy
		{
			int x;
			int y;
			int pattern;
			int enemyType;
		}EnemyInfo_t;

		typedef struct stageInfo
		{
			int enemyCount;
			EnemyInfo_t* enemies;
		}StageInfo_t;
		
		void LoadStageMetaFile();
		void LoadPatternFile();

		void Load() override;

		const StageInfo_t& GetStageInfo(unsigned int stageNumber) const;
		const PatternInfo_t& PatternInfo(unsigned int patternNumber) const;
		
		unsigned int GetTotalStageCount() const;
	private:
		unsigned int mStageCount;
		unsigned int mPatternFileCount;

		StageInfo_t* mStageInfo;
		PatternInfo_t* mPatternInfo;
	};
}
