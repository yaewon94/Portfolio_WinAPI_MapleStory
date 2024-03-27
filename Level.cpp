#include "PCH.h"
#include "Level.h"
#include "GameObject.h"

// 생성자
Level::Level(const wstring& name) : Entity(name)
{
}

// 소멸자
Level::~Level()
{
	// 레벨이 전환되도 플레이어같은 오브젝트는 지워지면 안되므로, 
	// 각 레벨에 맞게 오브젝트를 지우도록 구현
}

// 오브젝트 추가
void Level::AddObject(GameObject& object, LAYER_TYPE layer)
{
	assert(&object);
	
	if (objectMap.find(layer) == objectMap.end())
	{
		vector<GameObject*> objects;
		objects.push_back(&object);
		objectMap.insert(make_pair(layer, objects));
	}
	else
	{
		vector<GameObject*>& objects = objectMap.find(layer)->second;
		objects.push_back(&object);
	}
}

// 오브젝트 찾기
GameObject& Level::FindObject(LAYER_TYPE layer)
{
	if (objectMap.find(layer) == objectMap.end()) throw GameException(LAYER_NAME[(UINT)layer] + L" 오브젝트를 찾을 수 없습니다");
	return *(objectMap.find(layer)->second[0]);
}

// 초기화
void Level::Init()
{
	for (const auto& objects : objectMap)
	{
		for (const auto object : objects.second)
		{
			assert(object);
			object->Init();
		}
	}
}

// 매 프레임마다 호출
void Level::Tick()
{
	for (const auto& objects : objectMap)
	{
		for (const auto& object : objects.second)
		{
			assert(object);
			object->Tick();
		}
	}
}

// 매 프레임마다 호출
void Level::FinalTick()
{
	for (const auto& objects : objectMap)
	{
		for (const auto object : objects.second)
		{
			object->FinalTick();
		}
	}
}

// 렌더링
void Level::Render()
{
	for (const auto& objects : objectMap)
	{
		for (const auto object : objects.second)
		{
			object->Render();
		}
	}
}

// 현재 레벨의 오브젝트 모두 지우기
void Level::DeleteObjects()
{
	for (auto& objects : objectMap)
	{
		for (auto object : objects.second)
		{
			if (object != nullptr)
			{
				delete object;
				object = nullptr;
			}
		}

		objects.second.clear();
	}

	objectMap.clear();
}