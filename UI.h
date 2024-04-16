#pragma once
#include "GameObject.h"

// UI Å¬·¡½º
class UI : public GameObject
{
public:
	UI(const wstring& name, Vec2<float> pos, Vec2<int> scale=DEFAULT_OBJECT_SCALE);
	UI(const UI& origin);
	~UI();
	virtual UI* Clone() override { return new UI(*this); }

	virtual Vec2<float> GetRenderPos() override { return GetPos(); }
};