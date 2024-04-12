#include "PCH.h"
#include "InputManager.h"
#include "ActiveSkill.h"
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
	for (auto& pair : keyMap)
	{
		if (pair.second != nullptr)
		{
			delete pair.second;
			pair.second = nullptr;
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
	// 키 상태별 콜백 메소드 초기화
	stateCallbackMap.insert(make_pair(KEY_STATE::KEY_PRESSED, &IKeyEvent::OnKeyPressed));
	stateCallbackMap.insert(make_pair(KEY_STATE::KEY_DOWN, &IKeyEvent::OnKeyDown));
	stateCallbackMap.insert(make_pair(KEY_STATE::KEY_RELEASED, &IKeyEvent::OnKeyReleased));

	// 플레이어 관련 콜백 : 이동, 점프
	keyMap.insert(make_pair(KEY_CODE::LEFT, new KeyInfo{ KEY_TYPE::PLAYER }));
	keyMap.insert(make_pair(KEY_CODE::RIGHT, new KeyInfo{ KEY_TYPE::PLAYER }));
	keyMap.insert(make_pair(KEY_CODE::X, new KeyInfo{ KEY_TYPE::PLAYER }));

	// 스킬 콜백
	// TODO : 하드코딩 말고, 플레이어 사용가능 스킬 목록에서 가져와서 for문 돌려서 초기화 하기
	keyMap.insert(make_pair(KEY_CODE::SHIFT, new KeyInfo{ KEY_TYPE::SKILL }));
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

			// 키 상태 확인
			// [CHECK] 다른 키들은 손떼면 바로 0되는데 alt 종류는 적용이 안됨
			if (GetAsyncKeyState((int)keyCode))
			{
				if (curState == KEY_STATE::KEY_PRESSED) curState = KEY_STATE::KEY_DOWN;
				else if (curState == KEY_STATE::NONE || curState == KEY_STATE::KEY_RELEASED) curState = KEY_STATE::KEY_PRESSED;
			}
			else
			{
				if (curState == KEY_STATE::KEY_PRESSED || curState == KEY_STATE::KEY_DOWN) curState = KEY_STATE::KEY_RELEASED;
				else curState = KEY_STATE::NONE;
			}

			// 콜백 호출
			auto stateCallbackPair = stateCallbackMap.find(curState);
			if (stateCallbackPair != stateCallbackMap.end())
			{
				if (keyInfo->type == KEY_TYPE::PLAYER) (*player.*(stateCallbackPair->second))(keyCode);
				else if (keyInfo->type == KEY_TYPE::SKILL)(player->GetSkill(keyCode).*(stateCallbackPair->second))(keyCode);
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