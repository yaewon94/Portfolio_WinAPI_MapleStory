#include "PCH.h"
#include "UIManager.h"
#include "UI.h"
#include "Button.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "LevelManager.h"
#include "Player.h"
#include "FSM.h"

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
			LevelManager::GetInstance().DeleteObjectFromList(*pair.second);
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
	obj = new UI(L"��Ȱ�ڽ�", Vec2(960.f, 500.f), Vec2(300, 131), AssetManager::GetInstance().LoadTexture(L"UI_AlertBox_Revival", L"UI_AlertBox_Revival.png"));
	obj->AddChild(*new Button(L"��Ȱ�ڽ� ��ư", "AlertBox_Revival", Vec2(0.f, 42.f), Vec2(40, 16), AssetManager::GetInstance().LoadTexture(L"UI_BTN_OK", L"UI_BTN_OK.png"), &UIManager::OnClickBtnOK_AlertBox_Revival));
	UImap.insert(make_pair("AlertBox_Revival", obj));
}

// �� �����Ӹ��� ȣ��
void UIManager::Tick()
{
	if (InputManager::GetInstance().IsClicked())
	{
		// ���� ������ �ִ� UI �� ���� ���ʿ� ������ �� �ͺ��� Ŭ���� �ƴ��� �˻��Ѵ�
		auto& vecUI = LevelManager::GetInstance().FindObjects(LAYER_TYPE::UI);
		auto iter = vecUI.rbegin();

		// TODO : vector�� iterator �� ������ �ڸ��� ����Ʈó�� �ڵ����� �پ���� ����
		// �������� ���� ������Ʈ�� ���͸��� ����Ʈ�� �����ϴ°� ������
		for (; iter != vecUI.rend(); ++iter)
		{
			//if ((*iter) == nullptr) continue;

			// Ȱ��ȭ �� UI ��
			if ((*iter)->IsActive())
			{
				// ��ư���� Ȯ��
				Button* button = dynamic_cast<Button*>(*iter);
				if (button != nullptr)
				{
					// ��ǥ���
					auto mousePos = InputManager::GetInstance().GetMousePos();
					auto btn_pos = button->GetRenderPos();
					auto btn_halfScale = button->GetScale() * 0.5f;

					if (mousePos.x >= btn_pos.x - btn_halfScale.x
						&& mousePos.x <= btn_pos.x + btn_halfScale.x
						&& mousePos.y >= btn_pos.y - btn_halfScale.y
						&& mousePos.y <= btn_pos.y + btn_halfScale.y)
					{
						// �ݹ� ȣ��
						button->OnClick();
					}
				}
			}
		}
	}
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
		// ���� ������ ��ϵ��� ���� ���
		if (LevelManager::GetInstance().FindObject(*iter->second) == nullptr)
		{
			LevelManager::GetInstance().AddObject(*iter->second);
			ShowChildren(*iter->second);
		}
		// ��ϵ� ���
		else
		{
			(*iter->second).SetActive(true);
			SetActiveChildren(*iter->second, true);
		}
	}
}

// UI ������Ʈ ��Ȱ��ȭ
void UIManager::CloseUI(const string& Key)
{
	auto iter = UImap.find(Key);

	if (iter != UImap.end())
	{
		(*iter->second).SetActive(false);
		UIManager::GetInstance().SetActiveChildren((*iter->second), false);
	}
}

// �ڽ� UI Ȱ��ȭ, ��Ȱ��ȭ
void UIManager::SetActiveChildren(GameObject& me, bool flag)
{
	for (auto child : me.GetChildren(LAYER_TYPE::UI))
	{
		child->SetActive(flag);
		SetActiveChildren(*child, flag);
	}
}

// �ڽ� UI�� ���� ������ ����ؼ� �������� �� �ְ� ��
void UIManager::ShowChildren(GameObject& me)
{
	for (auto child : me.GetChildren(LAYER_TYPE::UI))
	{
		LevelManager::GetInstance().AddObject(*child);
		ShowChildren(*child);
	}
}

// [event] ��Ȱ�ڽ� Ȯ�� ��ư ����
void UIManager::OnClickBtnOK_AlertBox_Revival(Button& button)
{
	// UI ��Ȱ��ȭ
	UIManager::GetInstance().CloseUI(button.Key);

	// �÷��̾� ����Ʈ ���·� ��ȯ, ü�� 100% ȸ��
	Player* player = dynamic_cast<Player*>(LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER));
	if(player != nullptr)
	{
		FSM* fsm = player->GetComponent<FSM>();
		fsm->ChangeState(fsm->GetDefaultState());
		player->FillHP(player->GetMaxHP());
	}
}

//// UI ����
//void UIManager::DestroyUI(GameObject* obj)
//{
//	// �ֻ��� �θ� UI���� ã��
//	while (obj != nullptr)
//	{
//		GameObject* parent = obj->GetParent();
//		UI* ui = dynamic_cast<UI*>(parent);
//
//		if (ui == nullptr)
//		{
//			// ���� obj�� ����Ű�� �ִ� ���� ���� obj�� ���� �ֻ��� UI
//			LevelManager::GetInstance().DeleteObjectFromList(*obj);
//			//obj->Destroy(); // UI Manager ���� �����ϴ°Ŷ� ����� �ȉ�
//			break;
//		}
//		else
//		{
//			LevelManager::GetInstance().DeleteObjectFromList(*obj);
//			obj = parent;
//		}
//	}
//}