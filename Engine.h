#pragma once

// ���� ���α׷��� �ְ� ������ Ŭ����
class Engine final
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
	void ChangeWindowSize(Vec2 resolution);

private:
	void CreateDefaultGDIobject();
};