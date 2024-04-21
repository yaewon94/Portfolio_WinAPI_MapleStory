#include "PCH.h"
#include "Button.h"

// ������
Button::Button(const wstring& name, const string& Key, Vec2<float> pos, Vec2<int> scale, Texture* texture, ONCLICK_CALLBACK click_callback)
	: UI(name, pos, scale, texture)
	, Key(Key), click_callback(click_callback)
{
}

// ���� ������
Button::Button(const Button& origin) 
	: UI(origin)
	, Key(origin.Key), click_callback(origin.click_callback)
{
}

// �Ҹ���
Button::~Button()
{
	click_callback = nullptr;
}