#include "PCH.h"
#include "Level.h"
#include "GameObject.h"
#include "Camera.h"

// 생성자
Level::Level(const wstring& name) : name(name), mainCamera(new Camera)
{
	GameObject::SetMainCamera(mainCamera);
}

// 소멸자
Level::~Level()
{
	// 카메라 삭제
	if (mainCamera != nullptr)
	{
		delete mainCamera;
		mainCamera = nullptr;
	}
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
	// 카메라
	mainCamera->FinalTick();

	// 오브젝트
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