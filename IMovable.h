#pragma once

enum class MOVE_DIRECTION : int
{
	LEFT = -1, RIGHT = 1
};

// 움직이는 게임 오브젝트에게 이동 메소드를 제공하기 위한 인터페이스
// abstract class
class IMovable
{
protected:
	int speed = 1;
	MOVE_DIRECTION direction;

public:
	virtual void Move() = 0;
};