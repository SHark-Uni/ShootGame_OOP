#define _CRT_NON_CONFORMING_WCSTOK
#pragma warning( disable : 6387 6011)

#include <stdio.h>
#include <stdlib.h>
#include <cassert>

#include "StageLoader.h"

using namespace ShootingGame;

StageLoader::StageLoader(const WCHAR* fileName)
	:mStageCount(0),
	mStageInfo(nullptr)
{
	size_t fileNameLength = wcslen(fileName);
	mFileName = (WCHAR*)malloc(sizeof(WCHAR) * (fileNameLength + 1));

	assert(mFileName != nullptr);

	wcsncpy_s(mFileName, fileNameLength, fileName, fileNameLength);
	mFileName[fileNameLength] = L'\0';
}

void StageLoader::LoadStageMetaFile()
{
	FILE* fp;
	size_t fileSize;
	size_t bufferSize;
	_wfopen_s(&fp, mFileName, L"rb");

}

void StageLoader::LoadStageDetailFile()
{
	return;
}

const StageLoader::stageInfo_t& StageLoader::GetStageInfo() const
{
	stageInfo_t tmp;
	return tmp;
}

void StageLoader::Load()
{

}

StageLoader::~StageLoader()
{
	free(mFileName);
}