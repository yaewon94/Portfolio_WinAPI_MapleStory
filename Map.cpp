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
	// ����ī�޶� ���� �� ���� ����
	LevelManager::GetInstance().GetMainCamera()->SetCurrentMap(this);

	// ������Ʈ Ȱ��ȭ
	for (auto obj : managedObjs)
	{
		obj->SetActive(true);
	}
	
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

		managedObjs.push_back(LevelManager::GetInstance().FindObjects(LAYER_TYPE::ENEMY)[0]);
	}

	// �÷��̾� ��ǥ ����
	LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER)->SetOffset(DefaultPlayerPos);
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