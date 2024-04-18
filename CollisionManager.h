#pragma once

class Collider;

// 충돌 처리 매니저
class CollisionManager final
{
	SINGLETON(CollisionManager);

private:
	array<vector<Collider*>, (size_t)LAYER_TYPE::LAYER_TYPE_COUNT> colliders;
	map<std::pair<UINT, UINT>, bool> stateMap;	// 두 충돌체가 이전 프레임에도 충돌했는지 정보를 저장

public:
	void Tick();

	void AddCollider(Collider& collider);
	void RemoveCollider(Collider& collider);

private:
	void CollisionCheck(Collider& me);
	void ExecuteCollisionEvent(Collider& a, Collider& b, bool isOverlapped);
};