#pragma once

class GameObject;
class Button;
class UI;

// UI ���� Ŭ����
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
	// ========== �ݹ��Լ� ���� ==========
	//static void DestroyUI(GameObject* obj);
	static void OnClickBtnOK_AlertBox_Revival(Button& button);
};