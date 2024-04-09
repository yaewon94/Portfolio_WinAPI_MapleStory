#include "PCH.h"
#include "InputManager.h"
#include "ActiveSkill.h"
#include "Engine.h"
#include "LevelManager.h"
#include "SkillManager.h"
#include "GameObject.h"
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
		auto keyInfo = item.second;

		if (keyInfo != nullptr)
		{
			keyInfo->stateCallback_map = nullptr;
			delete keyInfo;
			keyInfo = nullptr;
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
	auto state_callback_map = make_shared<map<KEY_STATE, KEY_CALLBACK>>();
	state_callback_map->insert(make_pair(KEY_STATE::KEY_PRESSED, &IKeyEvent::OnKeyPressed));
	state_callback_map->insert(make_pair(KEY_STATE::KEY_DOWN, &IKeyEvent::OnKeyDown));

	// �÷��̾� ���� �ݹ� : �̵�, ����
	keyMap.insert(make_pair(KEY_CODE::LEFT, new KeyInfo{ KEY_TYPE::PLAYER, state_callback_map }));
	keyMap.insert(make_pair(KEY_CODE::RIGHT, new KeyInfo{ KEY_TYPE::PLAYER, state_callback_map }));
	keyMap.insert(make_pair(KEY_CODE::X, new KeyInfo{ KEY_TYPE::PLAYER, state_callback_map }));

	// ��ų �ݹ�
	keyMap.insert(make_pair(KEY_CODE::SHIFT, new KeyInfo{ KEY_TYPE::SKILL, state_callback_map }));
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
			auto& stateMap = keyInfo->stateCallback_map;

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
			auto stateMap_iter = stateMap->find(curState);
			if (stateMap_iter != stateMap->end())
			{
				if (keyInfo->type == KEY_TYPE::PLAYER) (*player.*(stateMap_iter->second))(keyCode);
				else if (keyInfo->type == KEY_TYPE::SKILL)(*SkillManager::GetInstance().GetSkill(keyCode).*(stateMap_iter->second))(keyCode);
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