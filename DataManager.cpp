#include "PCH.h"
#include "DataManager.h"
#include "SkillManager.h"

// 생성자
DataManager::DataManager()
{
}

// 소멸자
DataManager::~DataManager()
{
}

// 초기화
void DataManager::Init()
{
	// [임시 하드코딩 : 시간되면 로컬 json이나 DB에서 가져오는 방식으로 구현 예정]
	SkillManager::GetInstance().Init();
}