#pragma once

// Ű, ���콺 �Է� �� ȣ��Ǵ� �Լ��� �����ϱ� ���� �������̽�
class IKeyEvent
{
public:
	virtual void OnKeyPressed(KEY_CODE) = 0;
	virtual void OnKeyDown(KEY_CODE) = 0;
};