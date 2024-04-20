#pragma once

class GameObject;
class UI;

// UI 관리 클래스
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