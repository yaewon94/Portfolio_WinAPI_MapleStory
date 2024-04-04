#pragma once

// ���� ������Ʈ���� ���� �޼ҵ带 �����ϱ� ���� �������̽�
// abstract class
class IJumpable
{
protected:
	float jumpPower;

	IJumpable(float power = 700.f) : jumpPower(power) {}

public:
	virtual void Jump() = 0;
};