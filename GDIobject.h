#pragma once

// 윈도우 GDI 오브젝트 생성-소멸 자동화
class GDIobject
{
private:
	HDC	dc;
	HGDIOBJ	prevObj;

public:
	GDIobject(HDC dc, HGDIOBJ obj);
	~GDIobject();
};
