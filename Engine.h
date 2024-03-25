#pragma once

// ���� ���α׷��� �ְ� ������ Ŭ����
class Engine
{
	SINGLETON(Engine);

private:
	Vec2 resolution;
	HINSTANCE hInst;
	HWND hWnd;
	HDC mainDC;
	HDC subDC;
	HBITMAP subBitmap;

	HPEN pen;
	HBRUSH brush;

public:
	int Init(HINSTANCE hInst, HWND hWnd);
	void Progress();

private:
	void ChangeWindowSize(Vec2 resolution);
	void CreateDefaultGDIobject();
};