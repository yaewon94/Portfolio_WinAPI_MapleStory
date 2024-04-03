#pragma once

// 게임 오브젝트에게 점프 메소드를 제공하기 위한 인터페이스
// abstract class
class IJumpable
{
protected:
	int jumpPower;

	IJumpable(int power = 700) : jumpPower(power) {}

public:
	virtual void Jump() = 0;
};