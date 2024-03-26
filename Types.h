#pragma once

// 2차원 벡터
struct Vec2
{
	int x, y;
	Vec2(int x, int y) : x(x), y(y) {}
	Vec2(POINT point) : x(point.x), y(point.y) {}
};

// 레벨
enum class LEVEL_TYPE
{
	NONE, TEST
};