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
, subTex(nullptr) //, subDC(nullptr), subBitmap(nullptr)
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
	SkillManager::GetInstance().Tick();
	LevelManager::GetInstance().Tick();

	// ���ӸŴ��� FinalTick()
	LevelManager::GetInstance().FinalTick();
	CollisionManager::GetInstance().FinalTick();
	DebugRender::GetInstance().FinalTick();

	// ���� ȭ�� Clear
	HBRUSH prevBrush = (HBRUSH)SelectObject(subTex->GetDC(), brush);
	Rectangle(subTex->GetDC(), -1, -1, (int)resolution.x + 1, (int)resolution.y + 1);

	// ���ӸŴ��� ������
	LevelManager::GetInstance().Render();
	DebugRender::GetInstance().Render();

	// sub -> main ������
	BitBlt(mainDC, 0, 0, (int)resolution.x, (int)resolution.y, subTex->GetDC(), 0, 0, SRCCOPY);
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

// �ؽ�Ʈ ������
void Engine::Render(Vec2 pos, const wstring& text)
{
	SetBkMode(subTex->GetDC(), TRANSPARENT);
	TextOutW(subTex->GetDC(), (int)pos.x, (int)pos.y, text.c_str(), (int)text.length());
}

// ������ �������� �ʿ��� ������Ʈ ����
void Engine::CreateDefaultGDIobject()
{
	// DC(Device Context) : �Է� ������ ��Ʈ�ʿ� �������� �ϱ� ���� �ʿ��� �Ǽ��� ���� ����ü
	// ���� �����츦 Ÿ������ �����ϴ� DC ����
	mainDC = ::GetDC(hWnd);

	// ���� �����쿡 ��� ���� �̸� �׷����� �뵵�� �����ؽ�ó ����
	subTex = AssetManager::GetInstance().CreateTexture(L"SubTexture", (UINT)resolution.x, (UINT)resolution.y);

	/*
	// ���� DC ����
	// ���� �����쿡 ����ϱ� ���� �̸� �׸��� �׷����� �뵵
	subDC = CreateCompatibleDC(mainDC);

	// ���� ��Ʈ�� ����
	// �޸� �󿡸� �����ϴ� ��Ʈ�ʿ� �̸� �׷�����, �ѹ��� ������ ����
	subBitmap = CreateCompatibleBitmap(mainDC, (int)resolution.x, (int)resolution.y);


	// ����DC�� ������Ʈ���� �����ϰ� ��
	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(subDC, subBitmap);
	DeleteObject(hPrevBitmap);
	*/

	// ���� ����� �귯��, �� ����
	//brush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	brush = CreateSolidBrush(RGB(0, 0, 0));
}