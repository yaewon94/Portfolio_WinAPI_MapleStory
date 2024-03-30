#pragma once

class GameObject;

// 디버깅 모드 렌더링 클래스
class DebugRender final
{
	SINGLETON(DebugRender);

private:
	vector<Log*> renderLogs;
	GameObject* player;

public:
	void Init();
	void FinalTick();
	void Render();
};