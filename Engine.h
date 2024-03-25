#pragma once

// 게임 프로그램 전체 관리
class Engine
{
	SINGLETON(Engine);

public:
	int Init(HINSTANCE hInst, HWND hWnd, POINT resolution);
	void Progress();
};