#pragma once

class Texture;

// ���� ���α׷��� �ְ� ������ Ŭ����
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
	Texture* subTex;	// ���� ���۸� �뵵
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