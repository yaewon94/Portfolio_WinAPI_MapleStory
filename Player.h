#pragma once
#include "GameObject.h"
#include "IKeyEvent.h"
#include "IMovable.h"
#include "IJumpable.h"

class Player final : public GameObject, public IKeyEvent, IMovable, IJumpable
{
public:
	CSTR_COPY_ASSIGN(Player);
	Player(const wstring& name, Vec2 pos, Vec2 scale);
	~Player();

	virtual void OnKeyPressed(KEY_CODE key) override;
	virtual void OnKeyDown(KEY_CODE key) override;

private:
	virtual void Move() override;
	virtual void Jump() override;
};