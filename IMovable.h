#pragma once

// �����̴� ���� ������Ʈ���� �̵� �޼ҵ带 �����ϱ� ���� �������̽�
// abstract class
class IMovable
{
protected:
	int speed = 0;

public:
	virtual void Move() = 0;
};