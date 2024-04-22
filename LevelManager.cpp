#include "PCH.h"
#include "LevelManager.h"
#include "Level_Boss_Will_Phase1.h"
#include "DataManager.h"
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
		for (auto& layer : curLevel->objects)
		{
			for(auto obj : layer)
			{
				if(obj != nullptr) DeleteObject(*obj);
			}
		}

		delete curLevel;
		curLevel = nullptr;
	}
}

// 초기화
void LevelManager::Init()
{
	// 데이터 초기화
	DataManager::GetInstance().Init();

	// 초기 레벨 지정
	ChangeLevel(LEVEL_TYPE::BOSS_WILL_PHASE1);
}

// 매 프레임마다 호출
void LevelManager::Tick()
{
	assert(curLevel);
	curLevel->Tick();
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
		Log(LOG_TYPE::LOG_ERROR, L"현재 레벨과 변경하려는 레벨이 같습니다");
		return;
	}

	array<vector<GameObject*>, (size_t)LAYER_TYPE::LAYER_TYPE_COUNT> prevObjects;

	// 현재 레벨 Exit()
	if (curLevel != nullptr)
	{
		curLevel->Exit();

		// 현재 레벨에서 지우지 않은 오브젝트 저장
		for (int layer=0; layer<prevObjects.size(); ++layer)
		{
			for (auto object : curLevel->objects.at(layer))
			{
				prevObjects.at(layer).push_back(object);
			}
		}

		delete curLevel;
	}

	// 레벨 전환
	switch (level)
	{
	case LEVEL_TYPE::BOSS_WILL_PHASE1:
		curLevel = new Level_Boss_Will_Phase1;
		break;
	default:
		Log(LOG_TYPE::LOG_ERROR, L"바꾸려는 레벨이 없습니다");
		return;
	}

	// 이전 레벨의 남아있는 오브젝트 옮기기
	for (int layer=0; layer<prevObjects.size(); ++layer)
	{
		for (auto object : prevObjects.at(layer))
		{
			curLevel->objects.at(layer).push_back(object);
		}
	}

	// 현재 레벨 Enter(), 초기화
	curLevel->Enter();
	curLevel->Init();
}

// 현재 레벨에 오브젝트 추가
void LevelManager::AddObject(GameObject& obj)
{
	if(curLevel != nullptr) curLevel->objects[(size_t)obj.GetLayer()].push_back(&obj);
}

// 현재 레벨의 오브젝트 찾기
GameObject* LevelManager::FindObject(LAYER_TYPE layer)
{
	assert(curLevel);
	return curLevel->objects[(size_t)layer].at(0);
}

GameObject* LevelManager::FindObject(GameObject& obj)
{
	if (curLevel != nullptr)
	{
		for (auto item : curLevel->objects[(size_t)obj.GetLayer()])
		{
			if (&obj == item) return item;
		}
	}

	return nullptr;
}

vector<GameObject*>& LevelManager::FindObjects(LAYER_TYPE layer)
{
	assert(curLevel);

	return curLevel->objects[(size_t)layer];
}

// 현재 레벨의 오브젝트 리스트에서 삭제, 실제 객체 제거
void LevelManager::DeleteObject(GameObject& me)
{
	assert(curLevel);

	auto& objects = curLevel->objects[(int)me.GetLayer()];
	int size = objects.size();

	for (int i=0; i<size; ++i)
	{
		if (objects[i] != nullptr)
		{
			if (objects[i]->GetID() == me.GetID())
			{
				objects[i]->Destroy();
				objects[i] = nullptr;
			}
		}
	}
}