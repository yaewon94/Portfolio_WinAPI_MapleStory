#pragma once

class Collider;

// 디버깅 모드 렌더링 클래스
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