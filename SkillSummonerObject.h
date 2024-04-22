#pragma once
#include "GameObject.h"

class EnemyAttackSkill;
class SkillObject;

// 스킬 소환 오브젝트
class SkillSummonerObject : public GameObject
{
private:
	const int ObjCount;

private:
	EnemyAttackSkill* skill;
	vector<SkillObject*> skillObjects;
	vector<Vec2<float>> skillVelocityVec;
	Vec2<float> skillObjOffset = DEFAULT_OBJECT_POS;

public:
	SkillSummonerObject(const wstring& name, LAYER_TYPE layer, int objCount, EnemyAttackSkill& skill);
	SkillSummonerObject(const SkillSummonerObject& origin);
	~SkillSummonerObject();
	virtual SkillSummonerObject* Clone() override { return new SkillSummonerObject(*this); }

public:
	virtual void Init() override;

public:
	void UseSkill();
	void AddSkillVelocity(Vec2<float> velocity, int index) { skillVelocityVec[index] = velocity; }
	void SetSkillObjectOffset(float x, float y) { skillObjOffset = Vec2(x, y); }
};