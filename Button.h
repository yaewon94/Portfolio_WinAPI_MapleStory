#pragma once
#include "UI.h"

class Button;
class Texture;

// 버튼클릭 콜백 메소드
typedef void(* ONCLICK_CALLBACK)(Button&);

// 버튼 클래스
class Button : public UI
{
	friend class UIManager;

private:
	const string Key;	// 자기가 소속된 UI 오브젝트의 키값
	ONCLICK_CALLBACK click_callback;

private:
	Button(const wstring& name, const string& Key, Vec2<float> pos, Vec2<int> scale, Texture* texture, ONCLICK_CALLBACK click_callback);
	Button(const Button& origin);
	~Button();
	virtual Button* Clone() override { return new Button(*this); }

private:
	void OnClick() { click_callback(*this); }
};