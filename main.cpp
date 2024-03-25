// Portfolio_WinAPI_MapleStory.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "PCH.h"

#include <crtdbg.h>

#include "framework.h"
#include "Portfolio_WinAPI_MapleStory.h"
#include "Resource.h"

#include "Engine.h"

#define MAX_LOADSTRING 50
#define FULL_HD POINT{1920, 1080}

// 전역 변수:
HINSTANCE g_hInst;  // 현재 인스턴스입니다.
HWND g_hWnd;        // 메인 윈도우 핸들

WCHAR g_szTitle[MAX_LOADSTRING];        // 제목 표시줄 텍스트입니다.
WCHAR g_szWindowClass[MAX_LOADSTRING];  // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// SAL : 주석언어
// 프로그램 진입점
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // 메모리 누수 관련, 디버그 출력
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(215);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, g_szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PORTFOLIOWINAPIMAPLESTORY, g_szWindowClass, MAX_LOADSTRING);

    // 윈도우 클래스 등록
    MyRegisterClass(hInstance);

    // 커널 오브젝트 : OS 가 관리하는 오브젝트, 직접적인 접근이 불가능하고 ID 값을 통해서 제어함
    // 윈도우 생성
    g_hInst = hInstance;
    g_hWnd = CreateWindowW(g_szWindowClass, g_szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!g_hWnd) return FALSE;

    // 윈도우를 화면에 보여줄지 말지 설정
    ShowWindow(g_hWnd, true);
    UpdateWindow(g_hWnd);

    // 게임엔진 초기화
    if (FAILED(Engine::GetInstance()->Init(g_hInst, g_hWnd, FULL_HD)))
    {
        MessageBox(nullptr, L"게임엔진 초기화 실패", L"ERROR", MB_OK);
        return 0;
    }

    // 리소스(단축키 테이블 핸들 얻기)
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PORTFOLIOWINAPIMAPLESTORY));

    // 메세지 루프
    MSG msg;

    // 게임 프로그램에 맞게 메세지 루프 변경
    while (true)
    {
        // 메세지가 있었으면 true, 메세지가 없었으면 false 리턴
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // 꺼내온 메세지가 WM_QUIT 이면 프로그램 종료
            if (msg.message == WM_QUIT) break;

            // 꺼내온 메세지 처리
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // 메세지가 큐에 없을 때에는 게임 코드 실행
            Engine::GetInstance()->Progress();
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex = {};

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PORTFOLIOWINAPIMAPLESTORY));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    //wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PORTFOLIOWINAPIMAPLESTORY);
    wcex.lpszClassName = g_szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                // 모달 박스
                // 활성화 되어 있는 동안, 다른 윈도우 창에 이벤트 전달 X
                DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), g_hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
