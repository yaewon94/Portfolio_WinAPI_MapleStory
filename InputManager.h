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
		NONE = 0,				// ���� �����ӿ��� �ȴ�����, �̹����� �ȴ���
		KEY_PRESSED = 0x8000,	// ���� �����ӿ� �ȴ�����, �̹��� ����
		KEY_DOWN = 0x8001,		// ���� �����ӿ��� ������, �̹����� ����
		KEY_RELEASED = 1		// ���� �����ӿ� ������, �̹��� �ȴ���
	};

	// Ű �Է� Ÿ��
	enum class KEY_TYPE
	{
		MOVE, SKILL, UI
	};

	// Ű ����
	struct KeyInfo
	{
		KEY_TYPE type;
		map<KEY_STATE, KEY_CALLBACK> keyStateCallback; // Ű ���� - �ݹ� �޼ҵ� (1:1 ����)
		KeyInfo(KEY_TYPE type, map<KEY_STATE, KEY_CALLBACK> keyStateCallback) : type(type), keyStateCallback(keyStateCallback) {}
	};

private:
	map<KEY_CODE, KeyInfo*> keyMap;	// Ű �� - Ű ���� (1:N ����)
	Player* player;	// ����Ű�� �÷��̾� ��ü�� �޶��� �� �ֱ� ������ ���۷����� �޾ƿ��� �ȵ�

public:
	void Init();
	void Tick();
};