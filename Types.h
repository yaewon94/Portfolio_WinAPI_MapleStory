#pragma once

// 오브젝트 레이어 타입
enum class LAYER_TYPE
{
	BACKGROUND, GROUND, WALL
	, ENEMY, PLAYER
	, PLAYER_SKILL
	, UI
	, LAYER_TYPE_COUNT
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

// 오브젝트 상태
enum class OBJECT_STATE
{
	IDLE, WALK, TRACE, JUMP, ATTACK
	, UI_MOONLIGHT_GAUGE_0, UI_MOONLIGHT_GAUGE_20, UI_MOONLIGHT_GAUGE_40, UI_MOONLIGHT_GAUGE_60, UI_MOONLIGHT_GAUGE_80, UI_MOONLIGHT_GAUGE_100 // 윌 달빛게이지
};

// 2차원 벡터
template <typename T> requires std::is_arithmetic_v<T>
struct Vec2
{
	T x, y;

	// 생성자
	Vec2() : x(0), y(0) {}
	Vec2(T x, T y) : x(x), y(y) {}
	Vec2(POINT point) : x((T)point.x), y((T)point.y) {}

	// 상수
	static Vec2 Left() { return Vec2(-1, 0); }
	static Vec2 Right() { return Vec2(1, 0); }
	static Vec2 Up() { return Vec2(0, -1); }
	static Vec2 Down() { return Vec2(0, 1); }

	// 연산자 오버로딩
	Vec2 operator+(const Vec2& other) { return Vec2(x + other.x, y + other.y); }
	Vec2& operator+=(const Vec2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	Vec2 operator-(const Vec2 other) { return Vec2(x - other.x, y - other.y); }
	Vec2 operator*(float value) { return Vec2((T)(x*value), (T)(y*value)); }
	Vec2 operator/(int value)
	{
		assert(value != 0);
		return Vec2(x / value, y / value);
	}
	bool operator>(const Vec2& other) { return x * x + y * y > other.x * other.x + other.y * other.y; }
	bool operator!=(const Vec2& other) { return x != other.x || y != other.y; }

	// 두 벡터의 거리
	float GetDistance(const Vec2& other)
	{
		T diffX = x - other.x;
		T diffY = y - other.y;
		return sqrtf(diffX*diffX + diffY*diffY);
	}

	// 문자열 변환
	wstring to_wstring(const Vec2& vec)
	{
		return std::to_wstring(vec.x) + L" , " + std::to_wstring(vec.y);
	}
};