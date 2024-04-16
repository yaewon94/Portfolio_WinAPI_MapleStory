#pragma once

class Map;

// �� ���� Ŭ����
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