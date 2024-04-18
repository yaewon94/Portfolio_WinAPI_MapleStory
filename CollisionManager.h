#pragma once

class Collider;

// �浹 ó�� �Ŵ���
class CollisionManager final
{
	SINGLETON(CollisionManager);

private:
	array<vector<Collider*>, (size_t)LAYER_TYPE::LAYER_TYPE_COUNT> colliders;
	map<std::pair<UINT, UINT>, bool> stateMap;	// �� �浹ü�� ���� �����ӿ��� �浹�ߴ��� ������ ����

public:
	void Tick();

	void AddCollider(Collider& collider);
	void RemoveCollider(Collider& collider);

private:
	void CollisionCheck(Collider& me);
	void ExecuteCollisionEvent(Collider& a, Collider& b, bool isOverlapped);
};