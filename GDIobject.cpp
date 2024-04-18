#include "PCH.h"
#include "GDIObject.h"

// ������
GDIobject::GDIobject(HDC dc, HGDIOBJ obj) : dc(dc), prevObj(nullptr)
{
	prevObj = SelectObject(dc, obj);
}

// �Ҹ���
GDIobject::~GDIobject()
{
	SelectObject(dc, prevObj);
}