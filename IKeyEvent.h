#pragma once

// �Է°�
enum class KEY_CODE
{
	LEFT = VK_LEFT, RIGHT = VK_RIGHT,
	ALT = VK_MENU
};

// Ű, ���콺 �Է� �� ȣ��Ǵ� �Լ��� �����ϱ� ���� �������̽�
class IKeyEvent
{
public:
	virtual void OnKeyPressed(KEY_CODE) = 0;
	virtual void OnKeyDown(KEY_CODE) = 0;
};