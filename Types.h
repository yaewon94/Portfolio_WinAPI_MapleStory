#pragma once

// 2���� ����
struct Vec2
{
	int x, y;
	Vec2(int x, int y) : x(x), y(y) {}
	Vec2(POINT point) : x(point.x), y(point.y) {}
};

// ������Ʈ ���̾� Ÿ��
enum class LAYER_TYPE
{
	PLAYER, LAYER_TYPE_COUNT
};

// ����
enum class LEVEL_TYPE
{
	NONE, TEST
};

// �Է°�
enum class KEY_CODE
{
	LEFT=VK_LEFT, RIGHT=VK_RIGHT
};