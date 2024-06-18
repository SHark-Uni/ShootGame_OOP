//파일 로더 새롭게 만드는 중 ...
#if 0 
#define _CRT_NON_CONFORMING_WCSTOK
#pragma warning( disable : 6387 6011)

#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <string>

#include "StageLoader.h"

using namespace ShootingGame;

StageLoader::StageLoader()
	:mStageCount(0)
	, mCurStage(0)
{

}

void StageLoader::LoadStageFile()
{
	FILE* fp;
	
	const WCHAR* FILE_PATH = L"stage/stageInfo.txt";
	const WCHAR* FILE_PREFIX = L"stage/";
	const size_t PREFIX_LENGTH = wcslen(FILE_PREFIX);

	const size_t MAX_SIZE = 512;
	const WCHAR* delims = L"\t\r\n";

	WCHAR Buffer[MAX_SIZE] = { 0 , };
	WCHAR** fileNames;

	_wfopen_s(&fp, FILE_PATH, L"rb");

	//Read Header
	fgetws(Buffer, MAX_SIZE, fp);
	swscanf_s(Buffer, L"%d", &mStageCount);

	//Read Header
	fgetws(Buffer, MAX_SIZE, fp);

	fileNames = new WCHAR*[mStageCount];
	WCHAR* token;
	size_t tokenLengths;
	WCHAR* nextToken = nullptr;
	
	//Read File Names
	for (size_t i = 0; i < mStageCount; i++)
	{
		fgetws(Buffer, MAX_SIZE, fp);
		token = wcstok_s(Buffer, delims, &nextToken);
		
		tokenLengths = wcslen(token);
		fileNames[i] = new WCHAR[PREFIX_LENGTH + tokenLengths + 1];

		assert(fileNames[i] != nullptr);
		wcsncpy_s(fileNames[i], PREFIX_LENGTH + tokenLengths + 1, FILE_PREFIX, PREFIX_LENGTH);
		fileNames[i][PREFIX_LENGTH] = L'\0';

		wcscat_s(fileNames[i], PREFIX_LENGTH + tokenLengths + 1, token);
		fileNames[i][tokenLengths] = L'\0';
	}
	fclose(fp);
	fp = nullptr;

	//Read StageInfo
	mStageInfo = new stageInfo_t[mStageCount];
	memset(Buffer, 0, MAX_SIZE);
	token = nullptr;
	for (size_t i = 0; i < mStageCount; i++)
	{
		size_t EnemyCount;
		
		_wfopen_s(&fp, fileNames[i], L"rb");
		//Read Header
		fgetws(Buffer, MAX_SIZE, fp);

		fgetws(Buffer, MAX_SIZE, fp);
		swscanf_s(Buffer, L"%d", &(mStageInfo[i].EnemyCount));

		EnemyCount = mStageInfo[i].EnemyCount;
		mStageInfo[i].EnemyInfo = new EnemyInfo_t[EnemyCount];
		
		//Read Header
		fgetws(Buffer, MAX_SIZE, fp);

		//Read EnemyInfo from File
		EnemyInfo_t curEnemy;
		for (size_t j = 0; j < EnemyCount; j++)
		{
			curEnemy = mStageInfo[i].EnemyInfo[j];
			fgetws(Buffer, MAX_SIZE, fp);
			token = wcstok_s(Buffer, delims, &nextToken);
			swscanf_s(token, L"(%d,%d,%d)", &(curEnemy.x), &(curEnemy.y), &(curEnemy.movingPattern));
		}
	}

	for (size_t i = 0; i < mStageCount; i++)
	{
		delete[] fileNames[i];
	}
	delete[] fileNames;
	fileNames = nullptr;
}

const StageLoader::stageInfo_t& StageLoader::GetStageInfo() const
{
	return mStageInfo[mCurStage];
}

void StageLoader::GoNextStage()
{
	if (mStageCount > mCurStage)
	{
		++mCurStage;
	}
	return;
}

StageLoader::~StageLoader()
{
	for (size_t i = 0; i < mStageCount; i++)
	{
		delete[] (mStageInfo[i].EnemyInfo);
	}
	delete[] mStageInfo;
}
#endif