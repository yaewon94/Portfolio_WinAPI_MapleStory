#pragma once

class GameObject;
class Button;
class UI;

// UI 관리 클래스
class UIManager final
{
	SINGLETON(UIManager);

private:
	map<string, UI*> UImap;	// key, UI GameObject

public:
	void Init();
	void Tick();

public:
	void ShowUI(const string& Key);

private:
	void CloseUI(const string& Key);
	void SetActiveChildren(GameObject& me, bool flag);
	void ShowChildren(GameObject& me);

private:
	// ========== 콜백함수 모음 ==========
	//static void DestroyUI(GameObject* obj);
	static void OnClickBtnOK_AlertBox_Revival(Button& button);
};