#pragma once

// 2Â÷¿ø º¤ÅÍ
struct Vec2
{
	int x, y;
	Vec2() : x(0), y(0) {}
	Vec2(int x, int y) : x(x), y(y) {}
	Vec2(POINT point) : x(point.x), y(point.y) {}
};