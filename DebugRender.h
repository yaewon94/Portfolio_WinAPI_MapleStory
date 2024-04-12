#pragma once

class Collider;
class GameObject;

// ����� ��� ������ Ŭ����
class DebugRender final
{
	SINGLETON(DebugRender);

private:
	vector<Log*> renderLogs;
	vector<Collider*> colliders;
	GameObject* player;

public:
	void Init();
	void FinalTick();
	void Render();

	void AddCollider(Collider* collider) { colliders.push_back(collider); }
};