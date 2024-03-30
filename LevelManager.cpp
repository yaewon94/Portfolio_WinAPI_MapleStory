#include "PCH.h"
#include "LevelManager.h"
#include "Level.h"
#include "Level_Test.h"
#include "GameObject.h"

// 생성자
LevelManager::LevelManager() : level_ID(LEVEL_TYPE::NONE), curLevel(nullptr)
{
}

// 소멸자
LevelManager::~LevelManager()
{
	if (curLevel != nullptr)
	{
		curLevel->DeleteObjects();
		delete curLevel;
		curLevel = nullptr;
	}
}

// 초기화
void LevelManager::Init()
{
	// 초기 레벨 지정
	ChangeLevel(LEVEL_TYPE::TEST);
}

// 매 프레임마다 호출
void LevelManager::Tick()
{
	assert(curLevel);
	curLevel->Tick();
}

// 매 프레임마다 호출
void LevelManager::FinalTick()
{
	curLevel->FinalTick();
}

// 매 프레임마다 호출
void LevelManager::Render()
{
	curLevel->Render();
}

// 레벨 전환
void LevelManager::ChangeLevel(LEVEL_TYPE level)
{
	if (level_ID == level)
	{
		//Log(LOG_TYPE::LOG_ERROR, L"현재 레벨과 변경하려는 레벨이 같습니다");
		return;
	}

	// 현재 레벨 Exit()
	if (curLevel != nullptr) curLevel->Exit();

	// 레벨 전환
	switch (level)
	{
	case LEVEL_TYPE::TEST:
		curLevel = new Level_Test;
		break;
	default:
		//Log(LOG_TYPE::LOG_ERROR, L"바꾸려는 레벨이 없습니다");
		break;
	}

	// 현재 레벨 Enter(), 초기화
	curLevel->Enter();
	curLevel->Init();
}

// 현재 레벨의 오브젝트 찾기
GameObject* LevelManager::FindObject(LAYER_TYPE layer)
{
	assert(curLevel);
	return curLevel->FindObject(layer);
}