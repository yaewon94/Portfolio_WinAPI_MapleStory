#include "PCH.h"
#include "Level.h"
#include "GameObject.h"

// 생성자
Level::Level(const wstring& name) : name(name)
{
}

// 소멸자
Level::~Level()
{
	// 레벨이 전환되도 플레이어같은 오브젝트는 지워지면 안되므로, 
	// 각 레벨에 맞게 오브젝트를 지우도록 구현
}

// 현재 레벨에 게임오브젝트 추가
GameObject& Level::AddObject(LAYER_TYPE layer, const wstring& name, Vec2 pos, Vec2 scale)
{
	size_t layer_idx = (size_t)layer;
	GameObject* obj = nullptr;

	assert(layer_idx < objects.max_size());
	obj = &GameObject::Create(name, pos, scale);
	objects[layer_idx].push_back(obj);

	return *obj;
}

// 초기화
void Level::Init()
{
	for (auto& layer : objects)
	{
		for (auto object : layer)
		{
			assert(object);
			object->Init();
		}
	}
}

// 매 프레임마다 호출
void Level::Tick()
{
	for (auto& layer : objects)
	{
		for (auto object : layer)
		{
			object->Tick();
		}
	}
}

// 매 프레임마다 호출
void Level::FinalTick()
{
	for (auto& layer : objects)
	{
		for (auto object : layer)
		{
			object->FinalTick();
		}
	}
}

// 매 프레임마다 렌더링
void Level::Render()
{
	for (auto& layer : objects)
	{
		for (auto object : layer)
		{
			assert(object);
			object->Render();
		}
	}
}

// 게임오브젝트 찾기
GameObject* Level::FindObject(LAYER_TYPE layer)
{
	size_t layerIdx = (size_t)layer;

	assert(layerIdx < objects.size());

	if (objects[layerIdx][0] == nullptr) return nullptr;
	return objects[layerIdx][0];
}

// 현재 레벨의 오브젝트 모두 지우기
void Level::DeleteObjects()
{
	for (auto& layer : objects)
	{
		for (auto object : layer)
		{
			if (object != nullptr)
			{
				object->Destroy();
				object = nullptr;
			}
		}
	}
}