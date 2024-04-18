#pragma once

class Collider;

// ����� ��� ������ Ŭ����
class DebugRender final
{
	SINGLETON(DebugRender);

private:
	vector<Log*> renderLogs;
	vector<Collider*> colliders;
	bool isRender;

public:
	void Init();
	void FinalTick();
	void Render();

public:
	void AddCollider(Collider* collider) { colliders.push_back(collider); }
};