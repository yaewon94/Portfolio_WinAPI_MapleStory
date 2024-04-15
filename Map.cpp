#include "PCH.h"
#include "Map.h"
#include "Background.h"
#include "Camera.h"
#include "LevelManager.h"

// ������
Map::Map(const wstring& name, Vec2<float> pos, Vec2<int> scale, Texture& background)
	: name(name), pos(pos), scale(scale), background(&background)
{
}

// �Ҹ���
Map::~Map()
{
	// Texture ��ü ���Ŵ� AssetManager�� �����
	background = nullptr;
}

// �� ����
void Map::Enter()
{
	// ����ī�޶� ���� �� ���� ����
	LevelManager::GetInstance().GetMainCamera()->SetCurrentMap(this);
	
	// ��� ������Ʈ �� ����
	Background* obj_background = (Background*)LevelManager::GetInstance().FindObject(LAYER_TYPE::BACKGROUND);
	obj_background->Set(pos, scale, background);
}