#include "PCH.h"
#include "UI.h"
#include "Animation.h"

// ������
UI::UI(const wstring& name, Vec2<float> pos, Vec2<int> scale) 
	: GameObject(name, pos, scale, LAYER_TYPE::UI)
{
}

UI::UI(const wstring& name, Vec2<float> pos, Vec2<int> scale, Texture* texture) 
	: GameObject(name, pos, scale, LAYER_TYPE::UI)
{
	SetTexture(texture);
}

// ���� ������
UI::UI(const UI& origin) : GameObject(origin)
{
}

// �Ҹ���
UI::~UI()
{
}