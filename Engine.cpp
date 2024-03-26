#include "PCH.h"
#include "Engine.h"
#include "LevelManager.h"

# define FULL_HD Vec2{1920,1080}

// ������
Engine::Engine() : resolution(FULL_HD), hInst(nullptr), hWnd(nullptr), mainDC(nullptr)
, subDC(nullptr), subBitmap(nullptr)
, pen(nullptr), brush(nullptr)
{}

// �Ҹ���
Engine::~Engine()
{
	// Device Context �޸� ����
	// �ü���� ���� �����ϴ� ���̱� ������ delete�� �������� ����
	ReleaseDC(hWnd, mainDC);
	DeleteObject(brush);
	DeleteObject(pen);
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
	LevelManager::GetInstance()->Init();

    return S_OK;
}

// ���� ���� (�� �����Ӹ��� ȣ���)
// �� �����ӿ� �ؾ��� �۾��� �þ���� FPS ����
void Engine::Progress()
{
	// ���� ȭ�� Clear
	HBRUSH prevBrush = (HBRUSH)SelectObject(subDC, brush);
	Rectangle(subDC, -1, -1, resolution.x + 1, resolution.y + 1);
	SelectObject(subDC, prevBrush);

	// ���ӸŴ��� Tick()
	LevelManager::GetInstance()->Tick();

	// ���ӸŴ��� FinalTick()
	LevelManager::GetInstance()->FinalTick();

	// ���ӸŴ��� ������
	LevelManager::GetInstance()->Render();
	/*
	// ������ �׽�Ʈ
	HPEN prevPen = (HPEN)SelectObject(subDC, pen);
	Rectangle(subDC, left, left, right, right);
	left += 100;
	right += 100;
	SelectObject(subDC, prevPen);
	*/

	// sub -> main ������
	BitBlt(mainDC, 0, 0, resolution.x, resolution.y, subDC, 0, 0, SRCCOPY);
}

// ������ ũ�� ����
void Engine::ChangeWindowSize(Vec2 resolution)
{
	// �Էµ� �ػ󵵿� �°� ���� ������ ũ�� ���
	RECT rt{ 0, 0, resolution.x, resolution.y };

	// �޴� ��� ���ο� ���� ������ ũ�� ����
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	// ������ ũ�� ����
	// @param : (x,y)�»�� ��ǥ, (cx,cy)�ػ�
	SetWindowPos(hWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
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
	subBitmap = CreateCompatibleBitmap(mainDC, resolution.x, resolution.y);

	// ����DC�� ������Ʈ���� �����ϰ� ��
	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(subDC, subBitmap);
	DeleteObject(hPrevBitmap);
	
	// ���� ����� �귯��, �� ����
	brush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	//brush = CreateSolidBrush(RGB(255, 255, 255));
	pen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
}