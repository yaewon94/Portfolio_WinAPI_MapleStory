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
	assert((UINT)layer < objects.size());
	objects[(UINT)layer].push_back(&object);
}

// 오브젝트 찾기
GameObject& Level::FindObject(LAYER_TYPE layer)
{
	assert((UINT)layer < objects.size());
	return *(objects[(UINT)layer][0]);
}

// 초기화
void Level::Init()
{
	for (const auto& layer : objects)
	{
		for (const auto& object : layer)
		{
			assert(object);
			object->Init();
		}
	}
}

// 매 프레임마다 호출
void Level::Tick()
{
	for (const auto& layer : objects)
	{
		for (const auto& object : layer)
		{
			assert(object);
			object->Tick();
		}
	}
}

// 매 프레임마다 호출
void Level::FinalTick()
{
	for (const auto& layer : objects)
	{
		for (const auto& object : layer)
		{
			object->FinalTick();
		}
	}
}

// 렌더링
void Level::Render()
{
	for (const auto& layer : objects)
	{
		for (const auto& object : layer)
		{
			object->Render();
		}
	}
}

// 현재 레벨의 오브젝트 모두 지우기
void Level::DeleteObjects()
{
	for (auto& layer : objects)
	{
		for (auto& object : layer)
		{
			if (object != nullptr)
			{
				delete object;
				object = nullptr;
			}
		}

		layer.clear();
	}
}