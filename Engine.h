#pragma once

class Texture;

// 게임 프로그램의 최고 관리자 클래스
class Engine final
{
	SINGLETON(Engine);

private:
	Vec2 resolution;
	HINSTANCE hInst;
	HWND hWnd;
	HDC mainDC;
	//HDC subDC;
	//HBITMAP subBitmap;
	Texture* subTex;	// 더블 버퍼링 용도
	HBRUSH brush;

public:
	Vec2 GetResolution() const { return resolution; }
	bool IsWindowFocused() const { return hWnd == GetFocus(); }

	int Init(HINSTANCE hInst, HWND hWnd);
	void Progress();

	void CreateSubDC(HDC& hdc, HBITMAP& hBitmap, UINT width=0, UINT height=0);
	void ChangeWindowSize(Vec2 resolution);
	void Render(Vec2 pos, Vec2 scale);
	void Render(Vec2 pos, const wstring& text);

private:
	void CreateDefaultGDIobject();
};