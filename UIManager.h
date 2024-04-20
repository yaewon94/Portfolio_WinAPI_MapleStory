#pragma once

class GameObject;
class UI;

// UI ���� Ŭ����
class UIManager final
{
	SINGLETON(UIManager);

private:
	map<string, UI*> UImap;	// key, UI GameObject

public:
	void Init();

public:
	void ShowUI(const string& Key);

private:
	void ShowChildren(GameObject& me);
};