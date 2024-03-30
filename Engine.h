#pragma once

class GameObject;

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
	HBRUSH brush;

public:
	int Init(HINSTANCE hInst, HWND hWnd);
	void Progress();
	void ChangeWindowSize(Vec2 resolution);

	bool IsWindowFocused() const { return hWnd == GetFocus(); }
	void Render(const GameObject& obj);
	void Render(Vec2 pos, const wstring& text);

private:
	void CreateDefaultGDIobject();
};