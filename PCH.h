#pragma once

// ������Ʈ ��Ŭ�� > �Ӽ� > C/C++ > �̸� �����ϵ� ���
// > �����(/Yc)
// > �̸� �����ϵ� ��� ���Ϸ� ����

// ����ó��
#include <assert.h>

// ������ API
#include <Windows.h>
// TransParentBlt()
#pragma comment(lib, "Msimg32.lib")
// .png �ε�
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "GdiPlus.lib")
using namespace Gdiplus;
// ����
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

// �ڷᱸ��
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

// ����Ʈ ������
#include <memory>
using std::shared_ptr;
using std::make_shared;

// ����ó��
#include <stdexcept>

// ����� ���� �������
#include "DesignPatterns.h"
#include "Types.h"
#include "Constants.h"
#include "GDIobject.h"
#include "Log.h"
#include "Functions.h"