#pragma once

// 입력값
enum class KEY_CODE
{
	LEFT = VK_LEFT, RIGHT = VK_RIGHT,
	ALT = VK_MENU
};

// 키, 마우스 입력 시 호출되는 함수를 구현하기 위한 인터페이스
class IKeyEvent
{
public:
	virtual void OnKeyPressed(KEY_CODE) = 0;
	virtual void OnKeyDown(KEY_CODE) = 0;
};