#include "PCH.h"
#include "Map.h"
#include "Background.h"
#include "Camera.h"
#include "LevelManager.h"

// ������
Map::Map(const wstring& name, Vec2<float> pos, Vec2<int> scale, Texture& background, Vec2<float> DefaultPlayerPos)
	: name(name), pos(pos), scale(scale), background(&background), DefaultPlayerPos(DefaultPlayerPos)
{
}

// �Ҹ���
Map::~Map()
{
	// Texture ��ü ���Ŵ� AssetManager�� �����
	background = nullptr;

	// GameObject ��ü ���Ŵ� Level�� �����
	for (auto obj : managedObjs)
	{
		obj = nullptr;
	}
}

// �� ����
void Map::Enter()
{
	// ��� ������Ʈ �� ����
	Background* obj_background = (Background*)LevelManager::GetInstance().FindObject(LAYER_TYPE::BACKGROUND);
	obj_background->Set(pos, scale, background);

	// [�ӽ� �ϵ��ڵ�]
	// ������Ʈ ���� ��������
	if (name == L"ȸ���� ȸ��(�Ķ�)")
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
	else if (name == L"ȸ���� ȸ��(����)")
	{
		GameObject* obj = LevelManager::GetInstance().FindObject(LAYER_TYPE::GROUND);
		obj->Set(Vec2(0.f, 195.f), Vec2(1920, 10));

		auto& objs = LevelManager::GetInstance().FindObjects(LAYER_TYPE::WALL);
		objs[0]->Set(Vec2(-950.f, 40.f), Vec2(10, 300));
		objs[1]->Set(Vec2(950.f, 40.f), Vec2(10, 300));

		obj = LevelManager::GetInstance().FindObjects(LAYER_TYPE::ENEMY)[1];
		obj->SetOffset(Vec2(500.f, 140.f));
		managedObjs.push_back(obj);
	}

	// ������Ʈ Ȱ��ȭ
	for (auto obj : managedObjs)
	{
		obj->SetActive(true);
	}

	// �÷��̾� ��ǥ ����
	LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER)->SetOffset(DefaultPlayerPos);

	// ����ī�޶� ���� �� ���� ����
	LevelManager::GetInstance().GetMainCamera()->SetCurrentMap(this);
}

// �� ����
void Map::Exit()
{
	// �Ϻ� ������Ʈ ��Ȱ��ȭ
	for (auto obj : managedObjs)
	{
		obj->SetActive(false);
	}
}