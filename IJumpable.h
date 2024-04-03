#pragma once

// ���� ������Ʈ���� ���� �޼ҵ带 �����ϱ� ���� �������̽�
// abstract class
class IJumpable
{
protected:
	int jumpPower;

	IJumpable(int power = 700) : jumpPower(power) {}

public:
	virtual void Jump() = 0;
};