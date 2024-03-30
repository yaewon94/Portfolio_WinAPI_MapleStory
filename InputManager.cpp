#include "PCH.h"
#include "InputManager.h"
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
	for (auto& key : keyMap)
	{
		if (key.second != nullptr) key.second = nullptr;
	}

	keyMap.clear();
}

// �ʱ�ȭ
void InputManager::Init()
{
	// ====== ��� �ʱ�ȭ ======
	player = LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER)->GetComponent<Player>();
	assert(player);

	// ===== key ���� �ʱ�ȭ =====
	// �÷��̾� ���� �ݹ� : �̵�, ����
	map<KEY_STATE, KEY_CALLBACK> player_state_callback;
	player_state_callback.insert(make_pair(KEY_STATE::KEY_PRESSED, &IKeyEvent::OnKeyPressed));
	player_state_callback.insert(make_pair(KEY_STATE::KEY_DOWN, &IKeyEvent::OnKeyDown));

	auto playerKey = make_shared<KeyInfo>(KEY_TYPE::PLAYER, player_state_callback);
	keyMap.insert(make_pair(KEY_CODE::LEFT, playerKey));
	keyMap.insert(make_pair(KEY_CODE::RIGHT, playerKey));
	keyMap.insert(make_pair(KEY_CODE::ALT, playerKey));
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
			auto& keyInfo = key.second;

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
		}
	}
}