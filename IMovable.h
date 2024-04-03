#pragma once

// 움직이는 게임 오브젝트에게 이동 메소드를 제공하기 위한 인터페이스
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