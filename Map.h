#pragma once
#include "Entity.h"

class Level;
class Texture;

class GameObject;

// 맵 클래스
class Map final : public Entity
{
	friend class MapManager;
	NO_CSTR_COPY_ASSIGN(Map);

private:
	wstring name;
	Vec2<float> pos;		// 맵 좌표 (중앙 기준)
	Vec2<int> scale;		// 맵 크기
	Texture* background;	// 배경 이미지
	vector<GameObject*> managedObjs;	// 관리 목적의 오브젝트 (맵 퇴장시, 비활성화시킬 오브젝트 등)

	const Vec2<float> DefaultPlayerPos;	// 포탈 이동을 제외한 방법으로 맵에 왔을 때, 플레이어 오브젝트가 위치할 좌표

private:
	Map(const wstring& name, Vec2<float> pos, Vec2<int> scale, Texture& background, Vec2<float> defaultPlayerPos);
	~Map();

	void Enter();
	void Exit();

public:
	Vec2<float> GetPos() { return pos; }
	Vec2<int> GetScale() { return scale; }
};