#pragma once

#pragma once

// ������Ʈ ���̾� Ÿ��
enum class LAYER_TYPE
{
	PLAYER, LAYER_TYPE_COUNT
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

// 2���� ����
struct Vec2
{
	int x, y;

	Vec2(int x, int y) : x(x), y(y) {}
	Vec2(POINT point) : x(point.x), y(point.y) {}
};