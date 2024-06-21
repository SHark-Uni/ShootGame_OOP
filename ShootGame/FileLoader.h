#pragma once

#include <windows.h>

namespace ShootingGame
{
	class FileLoader
	{
	public:
		typedef struct enemy
		{
			int x;
			int y;
			int pattern;
		}EnemyInfo_t;

		typedef struct stageInfo
		{
			int enemyCount;
			EnemyInfo_t* enemies;
		}StageInfo_t;
		
		void LoadStageMetaFile();
		void LoadPatternFile();
		void GoNextStage();

		static FileLoader& GetInstance();
		const StageInfo_t& GetStageInfo() const;

	private:
		FileLoader();
		~FileLoader();

		FileLoader(const FileLoader& other) = delete;
		FileLoader(FileLoader&& other) = delete;

		FileLoader& operator=(const FileLoader& rhs) = delete;
		FileLoader& operator=(FileLoader&& rhs) = delete;

		static FileLoader _FileLoader;

		unsigned int mStageCount;
		unsigned int mCurStage;
		StageInfo_t* mStageInfo;
	};
}
