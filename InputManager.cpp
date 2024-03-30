#include "PCH.h"
#include "InputManager.h"
#include "Engine.h"
#include "LevelManager.h"
#include "GameObject.h"
#include "Player.h"

// 생성자
InputManager::InputManager() : player(nullptr)
{
}

// 소멸자
InputManager::~InputManager()
{
	for (auto& key : keyMap)
	{
		if (key.second != nullptr) key.second = nullptr;
	}

	keyMap.clear();
}

// 초기화
void InputManager::Init()
{
	// ====== 멤버 초기화 ======
	player = LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER)->GetComponent<Player>();
	assert(player);

	// ===== key 정보 초기화 =====
	// 플레이어 관련 콜백 : 이동, 점프
	map<KEY_STATE, KEY_CALLBACK> player_state_callback;
	player_state_callback.insert(make_pair(KEY_STATE::KEY_PRESSED, &IKeyEvent::OnKeyPressed));
	player_state_callback.insert(make_pair(KEY_STATE::KEY_DOWN, &IKeyEvent::OnKeyDown));

	auto playerKey = make_shared<KeyInfo>(KEY_TYPE::PLAYER, player_state_callback);
	keyMap.insert(make_pair(KEY_CODE::LEFT, playerKey));
	keyMap.insert(make_pair(KEY_CODE::RIGHT, playerKey));
	keyMap.insert(make_pair(KEY_CODE::ALT, playerKey));
}

// 매 프레임마다 호출
void InputManager::Tick()
{
	// 윈도우가 포커싱 상태일때만, 입력 감지
	if (Engine::GetInstance().IsWindowFocused())
	{
		for (auto& key : keyMap)
		{
			auto keyCode = key.first;
			auto& keyInfo = key.second;

			// 하나의 key가 가지고 있는 상태들
			for (auto& stateCallback : keyInfo->keyStateCallback)
			{
				auto state = stateCallback.first;
				auto callback = stateCallback.second;

				if (GetAsyncKeyState((UINT)keyCode) & (UINT)state)
				{
					if (keyInfo->type == KEY_TYPE::PLAYER) (*player.*callback)(keyCode);

					break; // 하나의 key 당 하나의 상태만 처리하도록 구현
				}
			}
		}
	}
}