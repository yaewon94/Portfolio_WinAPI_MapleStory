#pragma once
#include "UI.h"

class Button;
class Texture;

// ��ưŬ�� �ݹ� �޼ҵ�
typedef void(* ONCLICK_CALLBACK)(Button&);

// ��ư Ŭ����
class Button : public UI
{
	friend class UIManager;

private:
	const string Key;	// �ڱⰡ �Ҽӵ� UI ������Ʈ�� Ű��
	ONCLICK_CALLBACK click_callback;

private:
	Button(const wstring& name, const string& Key, Vec2<float> pos, Vec2<int> scale, Texture* texture, ONCLICK_CALLBACK click_callback);
	Button(const Button& origin);
	~Button();
	virtual Button* Clone() override { return new Button(*this); }

private:
	void OnClick() { click_callback(*this); }
};