#include "PCH.h"
#include "UI.h"
#include "Animation.h"

// 생성자
UI::UI(const wstring& name, Vec2<float> pos, Vec2<int> scale) 
	: GameObject(name, pos, scale, LAYER_TYPE::UI)
{
}

// 복사 생성자
UI::UI(const UI& origin) : GameObject(origin)
{
}

// 소멸자
UI::~UI()
{
}