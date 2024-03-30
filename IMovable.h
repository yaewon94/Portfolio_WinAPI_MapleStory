#pragma once

enum class MOVE_DIRECTION : int
{
	LEFT = -1, RIGHT = 1
};

// �����̴� ���� ������Ʈ���� �̵� �޼ҵ带 �����ϱ� ���� �������̽�
// abstract class
class IMovable
{
protected:
	int speed = 1;
	MOVE_DIRECTION direction;

public:
	virtual void Move() = 0;
};