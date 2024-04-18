#pragma once

// 프로젝트 우클릭 > 속성 > C/C++ > 미리 컴파일된 헤더
// > 만들기(/Yc)
// > 미리 컴파일된 헤더 파일로 설정

// 오류처리
#include <assert.h>

// 윈도우 API
#include <Windows.h>
// TransParentBlt()
#pragma comment(lib, "Msimg32.lib")
// .png 로딩
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "GdiPlus.lib")
using namespace Gdiplus;
// 사운드
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

// 자료구조
#include <array>
using std::array;
#include <vector>
using std::vector;
#include <list>
using std::list;
#include <map>
using std::map;
using std::make_pair;
#include <string>
using std::string;
using std::wstring;

// 스마트 포인터
#include <memory>
using std::shared_ptr;
using std::make_shared;

// 예외처리
#include <stdexcept>

// 사용자 정의 헤더파일
#include "DesignPatterns.h"
#include "Types.h"
#include "Constants.h"
#include "GDIobject.h"
#include "Log.h"
#include "Functions.h"