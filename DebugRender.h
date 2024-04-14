#pragma once

class Collider;

// ����� ��� ������ Ŭ����
class DebugRender final
{
	SINGLETON(DebugRender);

private:
	vector<Log*> renderLogs;
	vector<Collider*> colliders;

public:
	void Init();
	void FinalTick();
	void Render();

	void AddCollider(Collider* collider) { colliders.push_back(collider); }
};