#include "PCH.h"
#include "InputManager.h"
#include "ActiveSkill.h"
#include "Engine.h"
#include "LevelManager.h"
#include "GameObject.h"
#include "Player.h"

// ������
InputManager::InputManager() : player(nullptr)
{
}

// �Ҹ���
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

// �ʱ�ȭ
void InputManager::Init()
{
	// ====== ��� �ʱ�ȭ ======
	player = static_cast<Player*>(LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER));
	assert(player);

	// ===== key ���� �ʱ�ȭ =====
	// Ű ���º� �ݹ� �޼ҵ� �ʱ�ȭ
	stateCallbackMap.insert(make_pair(KEY_STATE::KEY_PRESSED, &IKeyEvent::OnKeyPressed));
	stateCallbackMap.insert(make_pair(KEY_STATE::KEY_DOWN, &IKeyEvent::OnKeyDown));
	stateCallbackMap.insert(make_pair(KEY_STATE::KEY_RELEASED, &IKeyEvent::OnKeyReleased));

	// �÷��̾� ���� �ݹ� : �̵�, ����
	keyMap.insert(make_pair(KEY_CODE::LEFT, new KeyInfo{ KEY_TYPE::PLAYER }));
	keyMap.insert(make_pair(KEY_CODE::RIGHT, new KeyInfo{ KEY_TYPE::PLAYER }));
	keyMap.insert(make_pair(KEY_CODE::X, new KeyInfo{ KEY_TYPE::PLAYER }));

	// ��ų �ݹ�
	// TODO : �ϵ��ڵ� ����, �÷��̾� ��밡�� ��ų ��Ͽ��� �����ͼ� for�� ������ �ʱ�ȭ �ϱ�
	keyMap.insert(make_pair(KEY_CODE::SHIFT, new KeyInfo{ KEY_TYPE::SKILL }));
}

// �� �����Ӹ��� ȣ��
void InputManager::Tick()
{
	// �����찡 ��Ŀ�� �����϶���, �Է� ����
	if (Engine::GetInstance().IsWindowFocused())
	{
		for (auto& key : keyMap)
		{
			auto keyCode = key.first;
			auto keyInfo = key.second;
			auto& curState = keyInfo->curState;

			// Ű ���� Ȯ��
			// [CHECK] �ٸ� Ű���� �ն��� �ٷ� 0�Ǵµ� alt ������ ������ �ȵ�
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

			// �ݹ� ȣ��
			auto stateCallbackPair = stateCallbackMap.find(curState);
			if (stateCallbackPair != stateCallbackMap.end())
			{
				if (keyInfo->type == KEY_TYPE::PLAYER) (*player.*(stateCallbackPair->second))(keyCode);
				else if (keyInfo->type == KEY_TYPE::SKILL)(player->GetSkill(keyCode).*(stateCallbackPair->second))(keyCode);
			}

			/*
			// [ERROR] 0x8001�� Ű�ٿ� ���θ� �� �� ����
			// �ϳ��� key�� ������ �ִ� ���µ�
			for (auto& stateCallback : keyInfo->keyStateCallback)
			{
				auto state = stateCallback.first;
				auto callback = stateCallback.second;

				if (GetAsyncKeyState((UINT)keyCode) & (UINT)state)
				{
					if (keyInfo->type == KEY_TYPE::PLAYER) (*player.*callback)(keyCode);

					break; // �ϳ��� key �� �ϳ��� ���¸� ó���ϵ��� ����
				}
			}
			*/

		}
	}
}