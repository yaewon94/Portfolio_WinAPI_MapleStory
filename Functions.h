#pragma once

// 매크로
// 윈도우 GDI
#define USE_PEN(DC, TYPE) GDIobject pen(DC, Engine::GetInstance().GetPen(PEN_TYPE::TYPE))
#define USE_BRUSH(DC, TYPE) GDIobject brush(DC, Engine::GetInstance().GetBrush(BRUSH_TYPE::TYPE))


// 문자열 처리
wstring to_wstring(const string& str);