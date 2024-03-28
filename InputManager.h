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
		NONE = 0,				// 이전 프레임에도 안눌리고, 이번에도 안눌림
		KEY_PRESSED = 0x8000,	// 이전 프레임에 안눌리고, 이번에 눌림
		KEY_DOWN = 0x8001,		// 이전 프레임에도 눌리고, 이번에도 눌림
		KEY_RELEASED = 1		// 이전 프레임에 눌리고, 이번에 안눌림
	};

	// 키 입력 타입
	enum class KEY_TYPE
	{
		MOVE, SKILL, UI
	};

	// 키 정보
	struct KeyInfo
	{
		KEY_TYPE type;
		map<KEY_STATE, KEY_CALLBACK> keyStateCallback; // 키 상태 - 콜백 메소드 (1:1 대응)
		KeyInfo(KEY_TYPE type, map<KEY_STATE, KEY_CALLBACK> keyStateCallback) : type(type), keyStateCallback(keyStateCallback) {}
	};

private:
	map<KEY_CODE, KeyInfo*> keyMap;	// 키 값 - 키 상태 (1:N 대응)
	Player* player;	// 가리키는 플레이어 객체가 달라질 수 있기 때문에 레퍼런스로 받아오면 안됨

public:
	void Init();
	void Tick();
};