#pragma once

// 키, 마우스 입력 시 호출되는 함수를 구현하기 위한 인터페이스
class IKeyEvent
{
public:
	virtual void OnKeyPressed(KEY_CODE) = 0;
	virtual void OnKeyDown(KEY_CODE) = 0;
};