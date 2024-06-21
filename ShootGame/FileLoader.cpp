#define _CRT_NON_CONFORMING_WCSTOK
#pragma warning( disable : 6387 6011)

#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <string>

#include "FileLoader.h"

using namespace ShootingGame;

FileLoader FileLoader::_FileLoader;

FileLoader::FileLoader()
	:mStageCount(0)
	,mCurStage(0)
	,mStageInfo(nullptr)
{

}

FileLoader& FileLoader::GetInstance()
{
	return _FileLoader;
}

void FileLoader::LoadStageMetaFile()
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
	mStageInfo = new StageInfo_t[mStageCount];
	memset(Buffer, 0, MAX_SIZE);
	token = nullptr;

	for (size_t i = 0; i < mStageCount; i++)
	{
		size_t EnemyCount;
		
		_wfopen_s(&fp, fileNames[i], L"rb");
		//Read Header
		fgetws(Buffer, MAX_SIZE, fp);

		fgetws(Buffer, MAX_SIZE, fp);
		swscanf_s(Buffer, L"%d", &(mStageInfo[i].enemyCount));

		EnemyCount = mStageInfo[i].enemyCount;
		mStageInfo[i].enemies = new EnemyInfo_t[EnemyCount];
		
		//Read Header
		fgetws(Buffer, MAX_SIZE, fp);

		//Read EnemyInfo from File
		for (size_t j = 0; j < EnemyCount; j++)
		{
			fgetws(Buffer, MAX_SIZE, fp);
			token = wcstok_s(Buffer, delims, &nextToken);
			swscanf_s(token, L"(%d,%d,%d)", &(mStageInfo[i].enemies[j].x), &(mStageInfo[i].enemies[j].y), &(mStageInfo[i].enemies[j].pattern));
		}
	}

	for (size_t i = 0; i < mStageCount; i++)
	{
		delete[] fileNames[i];
	}
	delete[] fileNames;
	fileNames = nullptr;
}

const FileLoader::StageInfo_t& FileLoader::GetStageInfo() const
{
	return mStageInfo[mCurStage];
}

void FileLoader::GoNextStage()
{
	if (mStageCount > mCurStage)
	{
		++mCurStage;
	}
	return;
}

void FileLoader::LoadPatternFile()
{

}

FileLoader::~FileLoader()
{
	for (size_t i = 0; i < mStageCount; i++)
	{
		delete[] (mStageInfo[i].enemies);
	}
	delete[] mStageInfo;
}
