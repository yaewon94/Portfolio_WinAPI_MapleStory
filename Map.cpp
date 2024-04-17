#include "PCH.h"
#include "Map.h"
#include "Background.h"
#include "Camera.h"
#include "LevelManager.h"

// 생성자
Map::Map(const wstring& name, Vec2<float> pos, Vec2<int> scale, Texture& background, Vec2<float> DefaultPlayerPos)
	: name(name), pos(pos), scale(scale), background(&background), DefaultPlayerPos(DefaultPlayerPos)
{
}

// 소멸자
Map::~Map()
{
	// Texture 객체 제거는 AssetManager가 담당함
	background = nullptr;

	// GameObject 객체 제거는 Level이 담당함
	for (auto obj : managedObjs)
	{
		obj = nullptr;
	}
}

#include "AssetManager.h"
// 맵 진입
void Map::Enter()
{
	// 배경 오브젝트 값 설정
	Background* obj_background = (Background*)LevelManager::GetInstance().FindObject(LAYER_TYPE::BACKGROUND);
	obj_background->Set(pos, scale, background); // Set()으로 한건 안사라지는데
	// [ERROR] SetTexture()로 하면 몇초있다 사라짐

	// [임시 하드코딩]
	// 오브젝트 정보 가져오기
	if (name == L"회절의 회랑(파랑)")
	{
		GameObject* obj = LevelManager::GetInstance().FindObject(LAYER_TYPE::GROUND);
		obj->Set(Vec2(0.f, 360.f), Vec2(1920, 10));

		auto& objs = LevelManager::GetInstance().FindObjects(LAYER_TYPE::WALL);
		objs[0]->Set(Vec2(-950.f, 200.f), Vec2(10, 300));
		objs[1]->Set(Vec2(950.f, 200.f), Vec2(10, 300));

		obj = LevelManager::GetInstance().FindObjects(LAYER_TYPE::ENEMY)[0];
		obj->SetOffset(Vec2(500.f, 300.f));
		managedObjs.push_back(obj);
	}
	else if (name == L"회절의 회랑(보라)")
	{
		GameObject* obj = LevelManager::GetInstance().FindObject(LAYER_TYPE::GROUND);
		obj->Set(Vec2(0.f, 280.f), Vec2(1920, 10));

		auto& objs = LevelManager::GetInstance().FindObjects(LAYER_TYPE::WALL);
		objs[0]->Set(Vec2(-950.f, 110.f), Vec2(10, 300));
		objs[1]->Set(Vec2(950.f, 110.f), Vec2(10, 300));

		obj = LevelManager::GetInstance().FindObjects(LAYER_TYPE::ENEMY)[1];
		obj->SetOffset(Vec2(500.f, 230.f));
		managedObjs.push_back(obj);
	}

	// 오브젝트 활성화
	for (auto obj : managedObjs)
	{
		obj->SetActive(true);
	}

	// 플레이어 좌표 설정
	LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER)->SetOffset(DefaultPlayerPos);

	// 메인카메라에 현재 맵 정보 설정
	LevelManager::GetInstance().GetMainCamera()->SetCurrentMap(this);
}

// 맵 퇴장
void Map::Exit()
{
	// 일부 오브젝트 비활성화
	for (auto obj : managedObjs)
	{
		obj->SetActive(false);
	}
}