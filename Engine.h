#pragma once
#include "Texture.h"

class Texture;

// ���� ���α׷��� �ְ� ������ Ŭ����
class Engine final
{
	SINGLETON(Engine);

private:
	Vec2<int> resolution;
	HINSTANCE hInst;
	HWND hWnd;
	HDC mainDC;
	//HDC subDC;
	//HBITMAP subBitmap;
	Texture* subTex;	// ���� ���۸� �뵵
	HBRUSH brush;

public:
	HDC& GetMainDC() { return mainDC; }
	HDC& GetSubDC() { return subTex->GetDC(); }
	Vec2<int> GetResolution() const { return resolution; }
	bool IsWindowFocused() const { return hWnd == GetFocus(); }

	int Init(HINSTANCE hInst, HWND hWnd);
	void Progress();

	void ChangeWindowSize(Vec2<int> resolution);
	void Render(Vec2<float> pos, Vec2<int> scale);
	void Render(Vec2<float> pos, const wstring& text);

private:
	void CreateDefaultGDIobject();
};