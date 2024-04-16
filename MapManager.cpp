#include "PCH.h"
#include "MapManager.h"
#include "Map.h"
#include "AssetManager.h"

// ������
MapManager::MapManager()
{
}

// �Ҹ���
MapManager::~MapManager()
{
	for (auto map : maps)
	{
		if (map != nullptr)
		{
			delete map;
			map = nullptr;
		}
	}
}

// �ʱ�ȭ
void MapManager::Init()
{
	maps.push_back(new Map(L"ȸ���� ȸ��(�Ķ�)", Vec2(0.f, 0.f), Vec2(1920, 1265), *AssetManager::GetInstance().LoadTexture(L"BossWill_Phase1_blue_background", L"BossWill_Phase1_blue_background.png"), Vec2(0.f, 300.f)));
	maps.push_back(new Map(L"ȸ���� ȸ��(����)", Vec2(0.f, 1265.f), Vec2(1920, 1265), *AssetManager::GetInstance().LoadTexture(L"BossWill_Phase1_pupple_background", L"BossWill_Phase1_pupple_background.png"), Vec2(0.f, -300.f)));
}

// �� ����
void MapManager::ChangeMap(Map* currentMap, Map* newMap)
{
	if(currentMap != nullptr) currentMap->Exit();
	newMap->Enter();
}