#pragma once

// �����̴� ���� ������Ʈ���� �̵� �޼ҵ带 �����ϱ� ���� �������̽�
// abstract class
class IMovable
{
protected:
	float speed;
	Vec2 dir;

	IMovable(float speed = 300.f) : speed(speed) {}

public:
	virtual void Move() = 0;
};