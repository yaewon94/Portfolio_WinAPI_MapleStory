#include "PCH.h"
#include "Engine.h"
#include "CollisionManager.h"
#include "DataManager.h"
#include "DebugRender.h"
#include "GameObject.h"
#include "InputManager.h"
#include "LevelManager.h"
#include "PathManager.h"
#include "TimeManager.h"

# define FULL_HD Vec2{1920,1080}

// ������
Engine::Engine() : resolution(FULL_HD), hInst(nullptr), hWnd(nullptr), mainDC(nullptr)
, subDC(nullptr), subBitmap(nullptr)
, brush(nullptr)
{}

// �Ҹ���
Engine::~Engine()
{
	// Device Context �޸� ����
	// �ü���� ���� �����ϴ� ���̱� ������ delete�� �������� ����
	ReleaseDC(hWnd, mainDC);
	DeleteObject(brush);
}

// �ʱ�ȭ
int Engine::Init(HINSTANCE hInst, HWND hWnd)
{
	// ��� �ʱ�ȭ
	this->hInst = hInst;
	this->hWnd = hWnd;

	// ������ ũ�� ����
	ChangeWindowSize(this->resolution);

	// DC ����
	CreateDefaultGDIobject();

	// ���ӸŴ��� �ʱ�ȭ
	PathManager::GetInstance().Init();
	DataManager::GetInstance().Init();
	TimeManager::GetInstance().Init();
	LevelManager::GetInstance().Init();
	InputManager::GetInstance().Init();
	DebugRender::GetInstance().Init();

	return S_OK;
}

// ���� ���� (�� �����Ӹ��� ȣ���)
// �� �����ӿ� �ؾ��� �۾��� �þ���� FPS ����
void Engine::Progress()
{
	// ���ӸŴ��� Tick()
	TimeManager::GetInstance().Tick();
	InputManager::GetInstance().Tick();
	LevelManager::GetInstance().Tick();

	// ���ӸŴ��� FinalTick()
	LevelManager::GetInstance().FinalTick();
	CollisionManager::GetInstance().FinalTick();
	DebugRender::GetInstance().FinalTick();

	// ���� ȭ�� Clear
	HBRUSH prevBrush = (HBRUSH)SelectObject(subDC, brush);
	Rectangle(subDC, -1, -1, (int)resolution.x + 1, (int)resolution.y + 1);
	SelectObject(subDC, prevBrush);

	// ���ӸŴ��� ������
	LevelManager::GetInstance().Render();
	DebugRender::GetInstance().Render();

	// sub -> main ������
	BitBlt(mainDC, 0, 0, (int)resolution.x, (int)resolution.y, subDC, 0, 0, SRCCOPY);
}

// ������ ũ�� ����
void Engine::ChangeWindowSize(Vec2 resolution)
{
	// �Էµ� �ػ󵵿� �°� ���� ������ ũ�� ���
	RECT rt{ 0, 0, (LONG)resolution.x, (LONG)resolution.y };

	// �޴� ��� ���ο� ���� ������ ũ�� ����
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	// ������ ũ�� ����
	// @param : (x,y)�»�� ��ǥ, (cx,cy)�ػ�
	SetWindowPos(hWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
}

// ������
// HDC, HWND�� Ŭ���� �ܺο� �����Ű�� �ʱ� ���� ������
void Engine::Render(Vec2 pos, Vec2 scale)
{
	// [�ӽ� �ڵ�]
	HPEN pen = CreatePen(PS_SOLID, 10, RGB(0, 0, 0));
	HPEN prevPen = (HPEN)SelectObject(subDC, pen);
	Rectangle(subDC, (int)pos.x, (int)pos.y, (int)(pos.x + scale.x), (int)(pos.y + scale.y));
	SelectObject(subDC, prevPen);
}

// �ؽ�Ʈ ������
void Engine::Render(Vec2 pos, const wstring& text)
{
	SetBkMode(subDC, TRANSPARENT);
	TextOutW(subDC, (int)pos.x, (int)pos.y, text.c_str(), (int)text.length());
}

// DC - ��Ʈ�� ����
void Engine::ConnectDC(HDC hdc, HBITMAP hBitmap)
{
	hdc = CreateCompatibleDC(mainDC);
	DeleteObject(SelectObject(hdc, hBitmap));
}

// ������ �������� �ʿ��� ������Ʈ ����
void Engine::CreateDefaultGDIobject()
{
	// DC(Device Context) : �Է� ������ ��Ʈ�ʿ� �������� �ϱ� ���� �ʿ��� �Ǽ��� ���� ����ü
	// ���� �����츦 Ÿ������ �����ϴ� DC ����
	mainDC = GetDC(hWnd);

	// ���� DC ����
	// ���� �����쿡 ����ϱ� ���� �̸� �׸��� �׷����� �뵵
	subDC = CreateCompatibleDC(mainDC);

	// ���� ��Ʈ�� ����
	// �޸� �󿡸� �����ϴ� ��Ʈ�ʿ� �̸� �׷�����, �ѹ��� ������ ����
	subBitmap = CreateCompatibleBitmap(mainDC, (int)resolution.x, (int)resolution.y);

	// ����DC�� ������Ʈ���� �����ϰ� ��
	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(subDC, subBitmap);
	DeleteObject(hPrevBitmap);

	// ���� ����� �귯��, �� ����
	//brush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	brush = CreateSolidBrush(RGB(255, 255, 255));
}