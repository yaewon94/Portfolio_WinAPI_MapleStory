#pragma once

class GameObject;

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
	Vec2 GetResolution() const { return resolution; }
	bool IsWindowFocused() const { return hWnd == GetFocus(); }
	void ChangeWindowSize(Vec2 resolution);

	int Init(HINSTANCE hInst, HWND hWnd);
	void Progress();

	void Render(Vec2 pos, Vec2 scale);
	void Render(Vec2 pos, const wstring& text);
	void ConnectDC(HDC hdc, HBITMAP hBitmap);

private:
	void CreateDefaultGDIobject();
};