#pragma once

// ������Ʈ ���̾� Ÿ��
enum class LAYER_TYPE
{
	BACKGROUND, GROUND, WALL
	, ENEMY, PLAYER
	, PLAYER_SKILL
	, UI
	, LAYER_TYPE_COUNT
};

// ������Ʈ ���̾� �̸�
// [check] wstring or wstring*
const wstring LAYER_NAME[] =
{
	L"Player"
};

// ����
enum class LEVEL_TYPE
{
	NONE, TEST
};

// ������Ʈ ����
enum class OBJECT_STATE
{
	NONE = -1
	, IDLE, WALK, TRACE, JUMP, ATTACK
	, ANIM_DEFAULT
	, MOONLIGHT_GAUGE_DISABLED, MOONLIGHT_GAUGE_ABLED
};

// 2���� ����
template <typename T> requires std::is_arithmetic_v<T>
struct Vec2
{
	T x, y;

	// ������
	Vec2() : x(0), y(0) {}
	Vec2(T x, T y) : x(x), y(y) {}
	Vec2(POINT point) : x((T)point.x), y((T)point.y) {}

	// ���
	static Vec2 Left() { return Vec2(-1, 0); }
	static Vec2 Right() { return Vec2(1, 0); }
	static Vec2 Up() { return Vec2(0, -1); }
	static Vec2 Down() { return Vec2(0, 1); }

	// ������ �����ε�
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

	// �� ������ �Ÿ�
	float GetDistance(const Vec2& other)
	{
		T diffX = x - other.x;
		T diffY = y - other.y;
		return sqrtf(diffX*diffX + diffY*diffY);
	}

	// ���ڿ� ��ȯ
	wstring to_wstring()
	{
		return std::to_wstring(x) + L" , " + std::to_wstring(y);
	}
};