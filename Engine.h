#pragma once

// ���� ���α׷� ��ü ����
class Engine
{
	SINGLETON(Engine);

public:
	int Init(HINSTANCE hInst, HWND hWnd, POINT resolution);
	void Progress();
};