#pragma once

class Map;

// 맵 관리 클래스
class MapManager final
{
	SINGLETON(MapManager);

private:
	vector<Map*> maps;

public:
	void Init();

	Map& GetMap(int index) { return *maps[index]; }
	void ChangeMap(Map* currentMap, Map* newMap);
};