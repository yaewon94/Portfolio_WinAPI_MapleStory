#include "PCH.h"
#include "LevelManager.h"
#include "Level_Test.h"

// 생성자
LevelManager::LevelManager() : level_ID(LEVEL_TYPE::NONE), curLevel(nullptr)
{
}

// 소멸자
LevelManager::~LevelManager()
{
	// 레벨매니저의 소멸자가 호출될 때는 게임이 종료될 때 이므로, 현재 레벨의 오브젝트 모두 제거
	curLevel->DeleteObjects();

	// 메모리 해제
	if (curLevel != nullptr)
	{
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
void LevelManager::ChangeLevel(const LEVEL_TYPE level)
{
	if (level_ID == level) throw GameException(L"현재 레벨과 변경하려는 레벨이 같습니다");

	// 현재 레벨 Exit()
	if (curLevel != nullptr)
	{
		curLevel->Exit();
		delete curLevel;
	}

	// 레벨 전환
	switch (level)
	{
	case LEVEL_TYPE::TEST:
		curLevel = new Level_Test;
		break;
	default:
		throw GameException(L"바꾸려는 레벨이 없습니다");
		break;
	}

	// 현재 레벨 Enter(), 초기화
	curLevel->Enter();
	curLevel->Init();
}