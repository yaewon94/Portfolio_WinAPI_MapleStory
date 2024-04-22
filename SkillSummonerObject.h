#pragma once
#include "GameObject.h"

class EnemyAttackSkill;
class SkillObject;

// 스킬 소환 오브젝트
class SkillSummonerObject : public GameObject
{
private:
	vector<SkillObject*> skillObjects;
	EnemyAttackSkill* skill;
	vector<Vec2<float>> skillVelocityVec;
	const int ObjCount;

public:
	SkillSummonerObject(const wstring& name, LAYER_TYPE layer, int objCount, EnemyAttackSkill& skill);
	SkillSummonerObject(const SkillSummonerObject& origin);
	~SkillSummonerObject();
	virtual SkillSummonerObject* Clone() override { return new SkillSummonerObject(*this); }

public:
	virtual void Init() override;

public:
	virtual void SetActive(bool flag) override;
	void AddSkillVelocity(Vec2<float> velocity, int index) { skillVelocityVec[index] = velocity; }
};