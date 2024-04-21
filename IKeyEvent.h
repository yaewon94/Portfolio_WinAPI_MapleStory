#pragma once

// �Է°�
enum class KEY_CODE
{
	LEFT = VK_LEFT, RIGHT = VK_RIGHT,
	SHIFT = VK_SHIFT,
	N = 'N', X = 'X',
	LBUTTON = VK_LBUTTON
};

// Ű, ���콺 �Է� �� ȣ��Ǵ� �Լ��� �����ϱ� ���� �������̽�
class IKeyEvent
{
public:
	// [CHECK]
	// �÷��̾� �̵�, ������ �÷��̾� �Լ��� �ƴ϶� ��ų�� �����ϸ� KEY_CODE �Ķ���� ����
	// ��ų ȣ���ϵ��� ȣ���� �� �ְ�, �Է�Ű�� �ٲ� �� ����
	virtual void OnKeyPressed(KEY_CODE) = 0;
	virtual void OnKeyDown(KEY_CODE) = 0;
	virtual void OnKeyReleased(KEY_CODE) = 0;
};