#include "PCH.h"
#include "Engine.h"

#include "InputManager.h"
#include "LevelManager.h"
#include "DebugRender.h"

# define FULL_HD Vec2{1920,1080}

// 생성자
Engine::Engine() : resolution(FULL_HD), hInst(nullptr), hWnd(nullptr), mainDC(nullptr)
, subDC(nullptr), subBitmap(nullptr)
, brush(nullptr)
{}

// 소멸자
Engine::~Engine()
{
	// Device Context 메모리 해제
	// 운영체제가 직접 관리하는 것이기 때문에 delete로 해제하지 않음
	ReleaseDC(hWnd, mainDC);
	DeleteObject(brush);
}

// 초기화
int Engine::Init(HINSTANCE hInst, HWND hWnd)
{	
	// 멤버 초기화
	this->hInst = hInst;
	this->hWnd = hWnd;

	// 윈도우 크기 변경
	ChangeWindowSize(this->resolution);
	
	// DC 생성
	CreateDefaultGDIobject();

	// 게임매니저 초기화
	LevelManager::GetInstance().Init();
	InputManager::GetInstance().Init();
	DebugRender::GetInstance().Init();

    return S_OK;
}

// 엔진 구동 (매 프레임마다 호출됨)
// 한 프레임에 해야할 작업이 늘어날수록 FPS 감소
void Engine::Progress()
{
	// 게임매니저 Tick()
	InputManager::GetInstance().Tick();
	LevelManager::GetInstance().Tick();

	// 게임매니저 FinalTick()
	LevelManager::GetInstance().FinalTick();
	DebugRender::GetInstance().FinalTick();

	// 이전 화면 Clear
	HBRUSH prevBrush = (HBRUSH)SelectObject(subDC, brush);
	Rectangle(subDC, -1, -1, resolution.x + 1, resolution.y + 1);
	SelectObject(subDC, prevBrush);

	// 게임매니저 렌더링
	LevelManager::GetInstance().Render();
	DebugRender::GetInstance().Render();

	// sub -> main 윈도우
	BitBlt(mainDC, 0, 0, resolution.x, resolution.y, subDC, 0, 0, SRCCOPY);
}

// 윈도우 크기 변경
void Engine::ChangeWindowSize(Vec2 resolution)
{
	// 입력된 해상도에 맞게 실제 윈도우 크기 계산
	RECT rt{ 0, 0, resolution.x, resolution.y };

	// 메뉴 사용 여부에 따라 윈도우 크기 설정
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	// 윈도우 크기 변경
	// @param : (x,y)좌상단 좌표, (cx,cy)해상도
	SetWindowPos(hWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
}

// 윈도우 렌더링에 필요한 오브젝트 생성
void Engine::CreateDefaultGDIobject()
{
	// DC(Device Context) : 입력 윈도우 비트맵에 렌더링을 하기 위해 필요한 실수값 정보 집합체
	// 메인 윈도우를 타겟으로 지정하는 DC 생성
	mainDC = GetDC(hWnd);

	// 보조 DC 생성
	// 메인 윈도우에 출력하기 전에 미리 그림을 그려놓는 용도
	subDC = CreateCompatibleDC(mainDC);

	// 보조 비트맵 생성
	// 메모리 상에만 존재하는 비트맵에 미리 그려놓고, 한번에 렌더링 송출
	subBitmap = CreateCompatibleBitmap(mainDC, resolution.x, resolution.y);

	// 보조DC가 보조비트맵을 지정하게 함
	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(subDC, subBitmap);
	DeleteObject(hPrevBitmap);
	
	// 자주 사용할 브러쉬, 펜 생성
	//brush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	brush = CreateSolidBrush(RGB(255, 255, 255));
}