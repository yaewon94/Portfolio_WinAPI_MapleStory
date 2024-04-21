#pragma once

// 입력값
enum class KEY_CODE
{
	LEFT = VK_LEFT, RIGHT = VK_RIGHT,
	SHIFT = VK_SHIFT,
	N = 'N', X = 'X',
	LBUTTON = VK_LBUTTON
};

// 키, 마우스 입력 시 호출되는 함수를 구현하기 위한 인터페이스
class IKeyEvent
{
public:
	// [CHECK]
	// 플레이어 이동, 점프도 플레이어 함수가 아니라 스킬로 구현하면 KEY_CODE 파라미터 없이
	// 스킬 호출하듯이 호출할 수 있고, 입력키도 바꿀 수 있음
	virtual void OnKeyPressed(KEY_CODE) = 0;
	virtual void OnKeyDown(KEY_CODE) = 0;
	virtual void OnKeyReleased(KEY_CODE) = 0;
};