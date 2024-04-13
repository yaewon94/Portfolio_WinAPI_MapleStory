#pragma once
#include "AliveObject.h"
#include "IKeyEvent.h"

class ActiveSkill;

class Player final : public AliveObject, public IKeyEvent
{
private:
	map<KEY_CODE, ActiveSkill*> skillKeyMap;

public:
	Player(const wstring& name, Vec2<float> pos, Vec2<int> scale);
	Player(const Player& origin);
	~Player();
	virtual Player* Clone() override { return new Player(*this); }

	ActiveSkill& GetSkill(KEY_CODE keyCode) { return *skillKeyMap.find(keyCode)->second; }

	virtual void Init() override;

	virtual void OnKeyPressed(KEY_CODE key) override;
	virtual void OnKeyDown(KEY_CODE key) override;
	virtual void OnKeyReleased(KEY_CODE key) override;

private:
	void AddSkillKeyMap(KEY_CODE keyCode, ActiveSkill& skill);
};