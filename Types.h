#pragma once

// 2차원 벡터
struct Vec2
{
	int x, y;

	Vec2(int x, int y) : x(x), y(y) {}
	Vec2(POINT point) : x(point.x), y(point.y) {}
};

// 오브젝트 레이어 타입
enum class LAYER_TYPE
{
	PLAYER
};

// 오브젝트 레이어 이름
static const wstring LAYER_NAME[] = 
{
	L"Player"
};

// 레벨
enum class LEVEL_TYPE
{
	NONE, TEST
};

// 로그 정보
struct Log
{
	Vec2 pos;
	wstring message;
};

// 입력값
enum class KEY_CODE
{
	LEFT=VK_LEFT, RIGHT=VK_RIGHT
};