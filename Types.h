#pragma once

#pragma once

// 오브젝트 레이어 타입
enum class LAYER_TYPE
{
	GROUND, ENEMY, PLAYER, PLAYER_SKILL, LAYER_TYPE_COUNT
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
	float x, y;

	Vec2() : x(0), y(0) {}
	Vec2(float x, float y) : x(x), y(y) {}
	Vec2(POINT point) : x((float)point.x), y((float)point.y) {}

	static Vec2 Left() { return Vec2(-1, 0); }
	static Vec2 Right() { return Vec2(1, 0); }
	static Vec2 Up() { return Vec2(0, -1); }
	static Vec2 Down() { return Vec2(0, 1); }

	Vec2 operator+(const Vec2& other) { return Vec2(this->x + other.x, this->y + other.y); }
	Vec2 operator-(const Vec2 other) { return Vec2(this->x - other.x, this->y - other.y); }
	Vec2 operator*(float i) { return Vec2(this->x*i, this->y*i); }
	Vec2 operator/(int i)
	{
		assert(i != 0);
		return Vec2(this->x / i, this->y / i);
	}
	Vec2& operator+=(const Vec2& other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}
};