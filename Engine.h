#pragma once

// 게임 프로그램의 최고 관리자 클래스
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
	HBRUSH brush;

public:
	const HWND& GetMainWindow() { return hWnd; }
	const HDC& GetSubDC() { return subDC; }

	int Init(HINSTANCE hInst, HWND hWnd);
	void Progress();
	void ChangeWindowSize(Vec2 resolution);

private:
	void CreateDefaultGDIobject();
};