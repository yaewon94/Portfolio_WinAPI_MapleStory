#pragma once

class Player;

// ����� ��� ������ Ŭ����
class DebugRender final
{
	SINGLETON(DebugRender);

private:
	vector<Log*> renderLogs;

	HDC DC;
	Player* player;

public:
	void Init();
	void FinalTick();
	void Render();
};