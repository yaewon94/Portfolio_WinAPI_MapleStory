#pragma once

// ������ GDI ������Ʈ ����-�Ҹ� �ڵ�ȭ
class GDIobject
{
private:
	HDC	dc;
	HGDIOBJ	prevObj;

public:
	GDIobject(HDC dc, HGDIOBJ obj);
	~GDIobject();
};
