#include "PCH.h"
#include "GDIObject.h"

// 持失切
GDIobject::GDIobject(HDC dc, HGDIOBJ obj) : dc(dc), prevObj(nullptr)
{
	prevObj = SelectObject(dc, obj);
}

// 社瑚切
GDIobject::~GDIobject()
{
	SelectObject(dc, prevObj);
}