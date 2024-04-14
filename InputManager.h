#pragma once
#include "IKeyEvent.h"

class Player;

// 사용자 입력 처리를 위한 클래스
class InputManager final
{
	SINGLETON(InputManager);

	typedef void(IKeyEvent::* KEY_CALLBACK)(KEY_CODE);		// 키 입력 시 콜백 메소드

	// 키 상태 타입
	enum class KEY_STATE
	{
		NONE// = 0,				// 이전 프레임에도 안눌리고, 이번에도 안눌림
		, KEY_PRESSED// = 0x8000,	// 이전 프레임에 안눌리고, 이번에 눌림
		, KEY_DOWN// = 0x8001,		// 이전 프레임에도 눌리고, 이번에도 눌림
		, KEY_RELEASED// = 1,		// 이전 프레임에 눌리고, 이번에 안눌림
	};

	// 키 입력 타입
	enum class KEY_TYPE
	{
		PLAYER, SKILL, UI
	};

	// 키 정보
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