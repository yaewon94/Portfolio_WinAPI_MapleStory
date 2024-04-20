#include "PCH.h"
#include "UIManager.h"
#include "UI.h"
#include "AssetManager.h"
#include "LevelManager.h"

// ������
UIManager::UIManager()
{
}

// �Ҹ���
UIManager::~UIManager()
{
 	for (auto& pair : UImap)
	{
		if (pair.second != nullptr)
		{
			LevelManager::GetInstance().DeleteObject(*pair.second);
			delete pair.second;
			pair.second = nullptr;
		}
	}
}

// �ʱ�ȭ
void UIManager::Init()
{
	UI* obj = nullptr;

	// ��Ȱ���� ��¹ڽ�
	obj = new UI(L"UI_AlertBox_Revival", Vec2(960.f, 500.f), Vec2(300, 131), AssetManager::GetInstance().LoadTexture(L"UI_AlertBox_Revival", L"UI_AlertBox_Revival.png"));
	obj->AddChild(*new UI(L"BTN_OK", Vec2(0.f, 42.f), Vec2(40, 16), AssetManager::GetInstance().LoadTexture(L"UI_BTN_OK", L"UI_BTN_OK.png")));
	UImap.insert(make_pair("AlertBox_Revival", obj));
}

// UI ȭ�鿡 ���
void UIManager::ShowUI(const string& Key)
{
	auto iter = UImap.find(Key);

	if (iter == UImap.end())
	{
		Log(LOG_TYPE::LOG_ERROR, L"�ش� KEY���� ���� UI�� �����ϴ�");
	}
	else
	{
		LevelManager::GetInstance().AddObject(*iter->second);
		ShowChildren(*iter->second);
	}
}

// �ڽ� UI�� ���� ������ ����ؼ� �������Ҽ� �ְ� ��
void UIManager::ShowChildren(GameObject& me)
{
	for (auto child : me.GetChildren(LAYER_TYPE::UI))
	{
		LevelManager::GetInstance().AddObject(*child);
		ShowChildren(*child);
	}
}