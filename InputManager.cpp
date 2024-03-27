#include "PCH.h"
#include "InputManager.h"

#include "Engine.h"
#include "LevelManager.h"
#include "Player.h"

// ������
InputManager::InputManager() : player(nullptr)
{
}

// �Ҹ���
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

// �ʱ�ȭ
void InputManager::Init()
{
	// ====== ��� �ʱ�ȭ ======
	player = (Player*)(&LevelManager::GetInstance().GetCurrentLevel().FindObject(LAYER_TYPE::PLAYER));
	
	// ===== key ���� �ʱ�ȭ =====
	// �̵�
	map<KEY_STATE, KEY_CALLBACK> move_state_callback;
	move_state_callback.insert(make_pair(KEY_STATE::KEY_PRESSED, &IKeyEvent::OnKeyPressed));
	move_state_callback.insert(make_pair(KEY_STATE::KEY_DOWN, &IKeyEvent::OnKeyDown));

	KeyInfo* leftKey = new KeyInfo(KEY_TYPE::MOVE, move_state_callback);
	KeyInfo* rightKey = new KeyInfo(KEY_TYPE::MOVE, move_state_callback);

	keyMap.insert(make_pair(KEY_CODE::LEFT, leftKey));
	keyMap.insert(make_pair(KEY_CODE::RIGHT, rightKey));
}

// �� �����Ӹ��� ȣ��
void InputManager::Tick()
{
	// �����찡 ��Ŀ�� �����϶���, �Է� ����
	if (Engine::GetInstance().GetMainWindow() == GetFocus())
	{
		for (auto& key : keyMap)
		{
			auto keyCode = key.first;
			auto keyInfo = key.second;

			// �ϳ��� key�� ������ �ִ� ���µ�
			for (auto& stateCallback : keyInfo->keyStateCallback)
			{
				auto state = stateCallback.first;
				auto callback = stateCallback.second;

				if (GetAsyncKeyState((UINT)keyCode) & (UINT)state)
				{
					if(keyInfo->type == KEY_TYPE::MOVE) (*player.*callback)(keyCode);

					break; // �ϳ��� key �� �ϳ��� ���¸� ó���ϵ��� ����
				}
			}
		}
	}
}