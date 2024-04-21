#include "PCH.h"
#include "UIManager.h"
#include "UI.h"
#include "Button.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "LevelManager.h"
#include "Player.h"
#include "FSM.h"

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
			LevelManager::GetInstance().DeleteObjectFromList(*pair.second);
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
	obj = new UI(L"부활박스", Vec2(960.f, 500.f), Vec2(300, 131), AssetManager::GetInstance().LoadTexture(L"UI_AlertBox_Revival", L"UI_AlertBox_Revival.png"));
	obj->AddChild(*new Button(L"부활박스 버튼", "AlertBox_Revival", Vec2(0.f, 42.f), Vec2(40, 16), AssetManager::GetInstance().LoadTexture(L"UI_BTN_OK", L"UI_BTN_OK.png"), &UIManager::OnClickBtnOK_AlertBox_Revival));
	UImap.insert(make_pair("AlertBox_Revival", obj));
}

// 매 프레임마다 호출
void UIManager::Tick()
{
	if (InputManager::GetInstance().IsClicked())
	{
		// 현재 레벨에 있는 UI 중 가장 위쪽에 렌더링 된 것부터 클릭이 됐는지 검사한다
		auto& vecUI = LevelManager::GetInstance().FindObjects(LAYER_TYPE::UI);
		auto iter = vecUI.rbegin();

		// TODO : vector의 iterator 라서 지워진 자리가 리스트처럼 자동으로 줄어들지 않음
		// 다음부턴 레벨 오브젝트를 벡터말고 리스트로 설계하는게 나을듯
		for (; iter != vecUI.rend(); ++iter)
		{
			//if ((*iter) == nullptr) continue;

			// 활성화 된 UI 중
			if ((*iter)->IsActive())
			{
				// 버튼인지 확인
				Button* button = dynamic_cast<Button*>(*iter);
				if (button != nullptr)
				{
					// 좌표계산
					auto mousePos = InputManager::GetInstance().GetMousePos();
					auto btn_pos = button->GetRenderPos();
					auto btn_halfScale = button->GetScale() * 0.5f;

					if (mousePos.x >= btn_pos.x - btn_halfScale.x
						&& mousePos.x <= btn_pos.x + btn_halfScale.x
						&& mousePos.y >= btn_pos.y - btn_halfScale.y
						&& mousePos.y <= btn_pos.y + btn_halfScale.y)
					{
						// 콜백 호출
						button->OnClick();
					}
				}
			}
		}
	}
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
		// 현재 레벨에 등록되지 않은 경우
		if (LevelManager::GetInstance().FindObject(*iter->second) == nullptr)
		{
			LevelManager::GetInstance().AddObject(*iter->second);
			ShowChildren(*iter->second);
		}
		// 등록된 경우
		else
		{
			(*iter->second).SetActive(true);
			SetActiveChildren(*iter->second, true);
		}
	}
}

// UI 오브젝트 비활성화
void UIManager::CloseUI(const string& Key)
{
	auto iter = UImap.find(Key);

	if (iter != UImap.end())
	{
		(*iter->second).SetActive(false);
		UIManager::GetInstance().SetActiveChildren((*iter->second), false);
	}
}

// 자식 UI 활성화, 비활성화
void UIManager::SetActiveChildren(GameObject& me, bool flag)
{
	for (auto child : me.GetChildren(LAYER_TYPE::UI))
	{
		child->SetActive(flag);
		SetActiveChildren(*child, flag);
	}
}

// 자식 UI도 현재 레벨에 등록해서 렌더링할 수 있게 함
void UIManager::ShowChildren(GameObject& me)
{
	for (auto child : me.GetChildren(LAYER_TYPE::UI))
	{
		LevelManager::GetInstance().AddObject(*child);
		ShowChildren(*child);
	}
}

// [event] 부활박스 확인 버튼 누름
void UIManager::OnClickBtnOK_AlertBox_Revival(Button& button)
{
	// UI 비활성화
	UIManager::GetInstance().CloseUI(button.Key);

	// 플레이어 디폴트 상태로 전환, 체력 100% 회복
	Player* player = dynamic_cast<Player*>(LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER));
	if(player != nullptr)
	{
		FSM* fsm = player->GetComponent<FSM>();
		fsm->ChangeState(fsm->GetDefaultState());
		player->FillHP(player->GetMaxHP());
	}
}

//// UI 제거
//void UIManager::DestroyUI(GameObject* obj)
//{
//	// 최상위 부모 UI까지 찾기
//	while (obj != nullptr)
//	{
//		GameObject* parent = obj->GetParent();
//		UI* ui = dynamic_cast<UI*>(parent);
//
//		if (ui == nullptr)
//		{
//			// 현재 obj가 가리키고 있는 것이 원래 obj가 속한 최상위 UI
//			LevelManager::GetInstance().DeleteObjectFromList(*obj);
//			//obj->Destroy(); // UI Manager 에서 관리하는거라 지우면 안됌
//			break;
//		}
//		else
//		{
//			LevelManager::GetInstance().DeleteObjectFromList(*obj);
//			obj = parent;
//		}
//	}
//}