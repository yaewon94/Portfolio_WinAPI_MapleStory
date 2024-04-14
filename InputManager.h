#pragma once
#include "IKeyEvent.h"

class Player;

// ����� �Է� ó���� ���� Ŭ����
class InputManager final
{
	SINGLETON(InputManager);

	typedef void(IKeyEvent::* KEY_CALLBACK)(KEY_CODE);		// Ű �Է� �� �ݹ� �޼ҵ�

	// Ű ���� Ÿ��
	enum class KEY_STATE
	{
		NONE// = 0,				// ���� �����ӿ��� �ȴ�����, �̹����� �ȴ���
		, KEY_PRESSED// = 0x8000,	// ���� �����ӿ� �ȴ�����, �̹��� ����
		, KEY_DOWN// = 0x8001,		// ���� �����ӿ��� ������, �̹����� ����
		, KEY_RELEASED// = 1,		// ���� �����ӿ� ������, �̹��� �ȴ���
	};

	// Ű �Է� Ÿ��
	enum class KEY_TYPE
	{
		PLAYER, SKILL, UI
	};

	// Ű ����
	struct KeyInfo
	{
		KEY_TYPE type;
		KEY_STATE curState = KEY_STATE::NONE;
		KeyInfo(KEY_TYPE type) : type(type) {}
	};

private:
	map<KEY_CODE, KeyInfo*> keyMap;
	map<KEY_STATE, KEY_CALLBACK> stateCallbackMap;
	Player* player;

public:
	void Init();
	void Tick();
};