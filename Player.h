#pragma once
#include "AliveObject.h"
#include "IKeyEvent.h"

class ActiveSkill;
class Map;

class Player final : public AliveObject, public IKeyEvent
{
private:
	map<KEY_CODE, ActiveSkill*> skillKeyMap;
	int currentSkillCost = 0;

	Map* currentMap;

public:
	Player(const wstring& name, int MaxHP=100);
	Player(const Player& origin);
	~Player();
	virtual Player* Clone() override { return new Player(*this); }

	ActiveSkill& GetSkill(KEY_CODE keyCode) { return *skillKeyMap.find(keyCode)->second; }
	void AddSkillKeyMap(KEY_CODE keyCode, ActiveSkill& skill);

	int GetCurrentSkillCost() const { return currentSkillCost; }

	// use, fill �ΰ��� ���������� change�ϳ��� ��� �Ǵµ� �������ϱ� �̹��� �׳� ����
	void UseSkillCost(int cost);
	void FillSkillCost(int cost);

	void ChangeMap(Map& map);

	virtual void Init() override;

	virtual void OnKeyPressed(KEY_CODE key) override;
	virtual void OnKeyDown(KEY_CODE key) override;
	virtual void OnKeyReleased(KEY_CODE key) override;

	virtual void OnCollisionEnter(GameObject& other) override;
};