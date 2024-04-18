#pragma once

// ��ũ��
// ������ GDI
#define USE_PEN(DC, TYPE) GDIobject pen(DC, Engine::GetInstance().GetPen(PEN_TYPE::TYPE))
#define USE_BRUSH(DC, TYPE) GDIobject brush(DC, Engine::GetInstance().GetBrush(BRUSH_TYPE::TYPE))


// ���ڿ� ó��
wstring to_wstring(const string& str);