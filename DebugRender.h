#pragma once

class GameObject;

// ����� ��� ������ Ŭ����
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