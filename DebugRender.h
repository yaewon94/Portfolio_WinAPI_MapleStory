#pragma once

class Collider;
class Player;

// ����� ��� ������ Ŭ����
class DebugRender final
{
	SINGLETON(DebugRender);

private:
	vector<Log*> renderLogs;
	vector<Collider*> colliders;
	Player* player;

public:
	void Init();
	void FinalTick();
	void Render();

	void AddCollider(Collider* collider) { colliders.push_back(collider); }
};