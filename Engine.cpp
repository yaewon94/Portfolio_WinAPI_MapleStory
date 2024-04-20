#include "PCH.h"
#include "Engine.h"
#include "AssetManager.h"
#include "CollisionManager.h"
#include "DataManager.h"
#include "DebugRender.h"
#include "GameObject.h"
#include "InputManager.h"
#include "LevelManager.h"
#include "PathManager.h"
#include "SkillManager.h"
#include "Texture.h"
#include "TimeManager.h"

# define FULL_HD Vec2{1920,1080}

// ������
Engine::Engine() : resolution(FULL_HD), hInst(nullptr), hWnd(nullptr), mainDC(nullptr)
, subDC(nullptr), subBitmap(nullptr)
, pens{}, brushes{}
//, subTex(nullptr)
{}

// �Ҹ���
Engine::~Engine()
{
	// Device Context �޸� ����
	// �ü���� ���� �����ϴ� ���̱� ������ delete�� �������� ����
	ReleaseDC(hWnd, mainDC);

	for (auto& pen : pens)
	{
		DeleteObject(pen);
	}

	for (auto& brush : brushes)
	{
		DeleteObject(brush);
	}
}

// ���� �ʱ�ȭ
int Engine::Init(HINSTANCE hInst, HWND hWnd)
{
	// ��� �ʱ�ȭ
	this->hInst = hInst;
	this->hWnd = hWnd;
	this->resolution = FULL_HD;

	// �Էµ� �ػ󵵸� �������� ���� ���� �������� ũ�⸦ ���
	RECT rt = { 0, 0, resolution.x, resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	// ������ ũ�� ����
	//SetWindowPos(this->hWnd, nullptr, 0, 0, resolution.x, resolution.y, 0);
	SetWindowPos(this->hWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// DC, ������ gdi ������Ʈ ����
	CreateDefaultGDIobject();

	// Init()
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
	// Tick()
	TimeManager::GetInstance().Tick();
	InputManager::GetInstance().Tick();
	SkillManager::GetInstance().Tick();
	LevelManager::GetInstance().Tick();
	CollisionManager::GetInstance().Tick();

	// FinalTick()
	DebugRender::GetInstance().FinalTick();

	// ȭ�� Clear
	{
		USE_BRUSH(subDC, BLACK);
		Rectangle(subDC, -1, -1, resolution.x + 1, resolution.y + 1);
	}

	// Render()
	LevelManager::GetInstance().Render();
	DebugRender::GetInstance().Render();

	// Sub -> Main
	BitBlt(mainDC, 0, 0, resolution.x, resolution.y, subDC, 0, 0, SRCCOPY);
}

// ������ ũ�� ����
void Engine::ChangeWindowSize(Vec2<int> resolution)
{
	// �Էµ� �ػ󵵿� �°� ���� ������ ũ�� ���
	RECT rt{ 0, 0, (LONG)resolution.x, (LONG)resolution.y };

	// �޴� ��� ���ο� ���� ������ ũ�� ����
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	// ������ ũ�� ����
	// @param : (x,y)�»�� ��ǥ, (cx,cy)�ػ�
	SetWindowPos(hWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
}

// �ؽ�Ʈ ������
void Engine::Render(Vec2<float> pos, const wstring& text)
{
	SetBkMode(subDC, TRANSPARENT);
	TextOutW(subDC, (int)pos.x, (int)pos.y, text.c_str(), (int)text.length());
}

// ������ �������� �ʿ��� ������Ʈ ����
void Engine::CreateDefaultGDIobject()
{
	// DC(Device Context) : �Է� ������ ��Ʈ�ʿ� �������� �ϱ� ���� �ʿ��� �Ǽ��� ���� ����ü
	// ���� �����츦 Ÿ������ �����ϴ� DC ����
	mainDC = ::GetDC(hWnd);

	// ���� DC ����
	// ���� �����쿡 ����ϱ� ���� �̸� �׸��� �׷����� �뵵
	subDC = CreateCompatibleDC(mainDC);

	// ���� ��Ʈ�� ����
	// �޸� �󿡸� �����ϴ� ��Ʈ�ʿ� �̸� �׷�����, �ѹ��� ������ ����
	subBitmap = CreateCompatibleBitmap(mainDC, (int)resolution.x, (int)resolution.y);

	// ����DC�� ������Ʈ���� �����ϰ� ��
	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(subDC, subBitmap);
	DeleteObject(hPrevBitmap);

	//// ���� �����쿡 ��� ���� �̸� �׷����� �뵵�� �����ؽ�ó ����
	//subTex = AssetManager::GetInstance().CreateTexture(L"SubTexture", (UINT)resolution.x, (UINT)resolution.y);
	
	// ���� ����� �귯��, �� ����
	pens[(int)PEN_TYPE::BLACK] = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	pens[(int)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	pens[(int)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	brushes[(int)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	brushes[(int)BRUSH_TYPE::WHITE] = (HBRUSH)GetStockObject(WHITE_BRUSH);
	brushes[(int)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
}