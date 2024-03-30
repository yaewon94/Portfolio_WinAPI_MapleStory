#pragma once

#pragma once

// 오브젝트 레이어 타입
enum class LAYER_TYPE
{
	PLAYER, LAYER_TYPE_COUNT
};

// 오브젝트 레이어 이름
// [check] wstring or wstring*
const wstring LAYER_NAME[] =
{
	L"Player"
};

// 레벨
enum class LEVEL_TYPE
{
	NONE, TEST
};

// 2차원 벡터
struct Vec2
{
	int x, y;

	Vec2(int x, int y) : x(x), y(y) {}
	Vec2(POINT point) : x(point.x), y(point.y) {}
};