#include "PCH.h"
#include "MapManager.h"
#include "Map.h"
#include "AssetManager.h"

// »ı¼ºÀÚ
MapManager::MapManager()
{
}

// ¼Ò¸êÀÚ
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

// ÃÊ±âÈ­
void MapManager::Init()
{
	maps.push_back(new Map(L"È¸ÀıÀÇ È¸¶û(ÆÄ¶û)", Vec2(0.f, 0.f), Vec2(1920, 1265), *AssetManager::GetInstance().LoadTexture(L"BossWill_Phase1_blue_background", L"BossWill_Phase1_blue_background.png"), Vec2(0.f, 300.f)));
	maps.push_back(new Map(L"È¸ÀıÀÇ È¸¶û(º¸¶ó)", Vec2(0.f, 1265.f), Vec2(1920, 1265), *AssetManager::GetInstance().LoadTexture(L"BossWill_Phase1_pupple_background", L"BossWill_Phase1_pupple_background.png"), Vec2(0.f, -300.f)));
}

// ¸Ê º¯°æ
void MapManager::ChangeMap(Map* currentMap, Map* newMap)
{
	if(currentMap != nullptr) currentMap->Exit();
	newMap->Enter();
}