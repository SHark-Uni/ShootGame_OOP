#define _CRT_NON_CONFORMING_WCSTOK
#pragma warning( disable : 6387 6011)

#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <string>

#include "FileLoader.h"

using namespace ShootingGame;

FileLoader::FileLoader()
	:mStageCount(0)
	,mPatternFileCount(0)
	,mStageInfo(nullptr)
	,mPatternInfo(nullptr)
{

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
		fileNames[i][PREFIX_LENGTH + tokenLengths] = L'\0';
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

		fclose(fp);
	}

	for (size_t i = 0; i < mStageCount; i++)
	{
		delete[] fileNames[i];
	}
	delete[] fileNames;
	fileNames = nullptr;
}

const FileLoader::StageInfo_t& FileLoader::GetStageInfo(unsigned int stageNumber) const
{
	if (stageNumber < mStageCount)
	{
		return mStageInfo[stageNumber];
	}
	return { 0, nullptr };
}

const FileLoader::PatternInfo_t& FileLoader::PatternInfo(unsigned int patternNumber) const
{
	if (patternNumber < mPatternFileCount)
	{
		return mPatternInfo[patternNumber];
	}
	
	return { 0 , nullptr };
}

void FileLoader::LoadPatternFile()
{
	FILE* fp;

	const WCHAR* FILE_PATH = L"pattern/patternInfo.txt";
	const WCHAR* FILE_PREFIX = L"pattern/";
	const size_t PREFIX_LENGTH = wcslen(FILE_PREFIX);
	
	const size_t MAX_SIZE = 512;
	const WCHAR* delims = L"\t\r\n";

	WCHAR Buffer[MAX_SIZE] = { 0, };
	WCHAR** fileNames;

	_wfopen_s(&fp, FILE_PATH, L"rb");

	//Read Header
	fgetws(Buffer, MAX_SIZE, fp);
	swscanf_s(Buffer, L"%d", &mPatternFileCount);

	//Read Header
	fgetws(Buffer, MAX_SIZE, fp);

	fileNames = new WCHAR * [mPatternFileCount];
	WCHAR* token;
	size_t tokenLengths;
	WCHAR* nextToken = nullptr;

	for (size_t i = 0; i < mPatternFileCount; i++)
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

	//Read Pattern
	mPatternInfo = new PatternInfo_t[mPatternFileCount];
	memset(Buffer, 0, MAX_SIZE);
	token = nullptr;

	for (size_t i = 0; i < mPatternFileCount; i++)
	{
		size_t patternCount;

		_wfopen_s(&fp, fileNames[i], L"rb");
		//Read Header
		fgetws(Buffer, MAX_SIZE, fp);

		fgetws(Buffer, MAX_SIZE, fp);
		swscanf_s(Buffer, L"%d", &(mPatternInfo[i].patternCount));

		patternCount = mPatternInfo[i].patternCount;
		mPatternInfo[i].patterns = new pos_t[patternCount];

		//Read Header
		fgetws(Buffer, MAX_SIZE, fp);

		//Read EnemyInfo from File
		for (size_t j = 0; j < patternCount; j++)
		{
			fgetws(Buffer, MAX_SIZE, fp);
			token = wcstok_s(Buffer, delims, &nextToken);
			swscanf_s(token, L"(%d,%d)", &(mPatternInfo[i].patterns[j].x), &(mPatternInfo[i].patterns[j].y));
		}
		fclose(fp);
	}

	for (size_t i = 0; i < mPatternFileCount; i++)
	{
		delete[] fileNames[i];
	}
	delete[] fileNames;
	fileNames = nullptr;
}

void FileLoader::Load()
{
	LoadStageMetaFile();
	LoadPatternFile();
}

FileLoader::~FileLoader()
{
	for (size_t i = 0; i < mStageCount; i++)
	{
		delete[] (mStageInfo[i].enemies);
	}
	delete[] mStageInfo;


	for (size_t i = 0; i < mPatternFileCount; i++)
	{
		delete[] mPatternInfo[i].patterns;
	}
	delete[] mPatternInfo;
}
