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
	for (auto& item : keyMap)
	{
		auto keyInfo = item.second;

		if (keyInfo != nullptr)
		{
			keyInfo->stateCallback_map = nullptr;
			delete keyInfo;
			keyInfo = nullptr;
		}
	}
}

// 초기화
void InputManager::Init()
{
	// ====== 멤버 초기화 ======
	player = static_cast<Player*>(LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER));
	assert(player);

	// ===== key 정보 초기화 =====
	// 플레이어 관련 콜백 : 이동, 점프
	auto player_callback = make_shared<map<KEY_STATE, KEY_CALLBACK>>();
	player_callback->insert(make_pair(KEY_STATE::KEY_PRESSED, &IKeyEvent::OnKeyPressed));
	player_callback->insert(make_pair(KEY_STATE::KEY_DOWN, &IKeyEvent::OnKeyDown));

	keyMap.insert(make_pair(KEY_CODE::LEFT, new KeyInfo {KEY_TYPE::PLAYER, player_callback}));
	keyMap.insert(make_pair(KEY_CODE::RIGHT, new KeyInfo {KEY_TYPE::PLAYER, player_callback }));
	keyMap.insert(make_pair(KEY_CODE::ALT, new KeyInfo {KEY_TYPE::PLAYER, player_callback }));
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
			auto keyInfo = key.second;
			auto& curState = keyInfo->curState;
			auto& stateMap = keyInfo->stateCallback_map;

			// [문제] 이동중에 점프를 누르면 이동도 안되고, 점프도 안됨. 일단 점프가 되게하자
			// 키 상태 확인
			if (GetAsyncKeyState((int)keyCode))
			{
				if (curState == KEY_STATE::KEY_PRESSED) curState = KEY_STATE::KEY_DOWN;
				else curState = KEY_STATE::KEY_PRESSED;
			}
			else
			{
				if (curState == KEY_STATE::KEY_DOWN) curState = KEY_STATE::KEY_RELEASED;
				else curState = KEY_STATE::NONE;
			}

			// 콜백 호출
			auto stateMap_iter = stateMap->find(curState);
			if (stateMap_iter != stateMap->end())
			{
				if (keyInfo->type == KEY_TYPE::PLAYER) (*player.*(stateMap_iter->second))(key.first);
			}

			/*
			// [ERROR] 0x8001로 키다운 여부를 알 수 없음
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
			*/
			
		}
	}
}