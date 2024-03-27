#include "PCH.h"
#include "InputManager.h"

#include "Engine.h"
#include "LevelManager.h"
#include "Player.h"

// 생성자
InputManager::InputManager() : player(nullptr)
{
}

// 소멸자
InputManager::~InputManager()
{
	for (auto& item : keyMap)
	{
		if (item.second != nullptr)
		{
			delete item.second;
			item.second = nullptr;
		}
	}

	keyMap.clear();
}

// 초기화
void InputManager::Init()
{
	// ====== 멤버 초기화 ======
	player = (Player*)(&LevelManager::GetInstance().GetCurrentLevel().FindObject(LAYER_TYPE::PLAYER));
	
	// ===== key 정보 초기화 =====
	// 이동
	map<KEY_STATE, KEY_CALLBACK> move_state_callback;
	move_state_callback.insert(make_pair(KEY_STATE::KEY_PRESSED, &IKeyEvent::OnKeyPressed));
	move_state_callback.insert(make_pair(KEY_STATE::KEY_DOWN, &IKeyEvent::OnKeyDown));

	KeyInfo* leftKey = new KeyInfo(KEY_TYPE::MOVE, move_state_callback);
	KeyInfo* rightKey = new KeyInfo(KEY_TYPE::MOVE, move_state_callback);

	keyMap.insert(make_pair(KEY_CODE::LEFT, leftKey));
	keyMap.insert(make_pair(KEY_CODE::RIGHT, rightKey));
}

// 매 프레임마다 호출
void InputManager::Tick()
{
	// 윈도우가 포커싱 상태일때만, 입력 감지
	if (Engine::GetInstance().GetMainWindow() == GetFocus())
	{
		for (auto& key : keyMap)
		{
			auto keyCode = key.first;
			auto keyInfo = key.second;

			// 하나의 key가 가지고 있는 상태들
			for (auto& stateCallback : keyInfo->keyStateCallback)
			{
				auto state = stateCallback.first;
				auto callback = stateCallback.second;

				if (GetAsyncKeyState((UINT)keyCode) & (UINT)state)
				{
					if(keyInfo->type == KEY_TYPE::MOVE) (*player.*callback)(keyCode);

					break; // 하나의 key 당 하나의 상태만 처리하도록 구현
				}
			}
		}
	}
}