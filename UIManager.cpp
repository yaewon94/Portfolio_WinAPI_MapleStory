#include "PCH.h"
#include "UIManager.h"
#include "UI.h"
#include "AssetManager.h"
#include "LevelManager.h"

// 생성자
UIManager::UIManager()
{
}

// 소멸자
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

// 초기화
void UIManager::Init()
{
	UI* obj = nullptr;

	// 부활여부 출력박스
	obj = new UI(L"UI_AlertBox_Revival", Vec2(960.f, 500.f), Vec2(300, 131), AssetManager::GetInstance().LoadTexture(L"UI_AlertBox_Revival", L"UI_AlertBox_Revival.png"));
	obj->AddChild(*new UI(L"BTN_OK", Vec2(0.f, 42.f), Vec2(40, 16), AssetManager::GetInstance().LoadTexture(L"UI_BTN_OK", L"UI_BTN_OK.png")));
	UImap.insert(make_pair("AlertBox_Revival", obj));
}

// UI 화면에 출력
void UIManager::ShowUI(const string& Key)
{
	auto iter = UImap.find(Key);

	if (iter == UImap.end())
	{
		Log(LOG_TYPE::LOG_ERROR, L"해당 KEY값을 가진 UI가 없습니다");
	}
	else
	{
		LevelManager::GetInstance().AddObject(*iter->second);
		ShowChildren(*iter->second);
	}
}

// 자식 UI도 현재 레벨에 등록해서 렌더링할수 있게 함
void UIManager::ShowChildren(GameObject& me)
{
	for (auto child : me.GetChildren(LAYER_TYPE::UI))
	{
		LevelManager::GetInstance().AddObject(*child);
		ShowChildren(*child);
	}
}