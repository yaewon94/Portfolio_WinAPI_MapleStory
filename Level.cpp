#include "PCH.h"
#include "Level.h"
#include "Camera.h"
#include "Map.h"

// static 멤버 초기화
Camera* Level::mainCamera = new Camera;

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

// 초기화
void Level::Init()
{
	// 카메라
	mainCamera->Init();

	// 오브젝트
	for (auto& layer : objects)
	{
		for (auto object : layer)
		{
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
			if (object->IsActive()) object->Tick();
		}
	}
}

// 매 프레임마다 호출
void Level::FinalTick()
{
	// 카메라
	mainCamera->FinalTick();

	// 오브젝트
	for (auto& layer : objects)
	{
		for (auto object : layer)
		{
			if (object->IsActive()) object->FinalTick();
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
			if (object->IsActive()) object->Render();
		}
	}
}

// 게임오브젝트 찾기
GameObject* Level::FindObject(LAYER_TYPE layer)
{
	GameObject* obj = objects[(size_t)layer][0];
	return obj;
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