#pragma once
#include "ActiveSkill.h"

class AttackSkillModule;
class GameObject;
class Skill;
class PlayerAttackSkill;

// 스킬 관리 클래스
class SkillManager final
{
	SINGLETON(SkillManager);

private:
	vector<Skill*> skills;
	list<std::pair<AttackSkillModule*, GameObject*>> reservedSkills;	 // 딜레이 타임이 있는 스킬들 스킬오브젝트 활성화 준비용도

public:
	void Init();
	void Tick();

	Skill& GetSkill(size_t index) { return *skills.at(index); }
	void LaunchSkill(AttackSkillModule* skill, GameObject* skillObj) { reservedSkills.push_back(make_pair(skill, skillObj)); }
	void SetValid(ActiveSkill* skill, bool flag) { skill->isValid = flag; }

private:
	// ========== 스킬 콜백함수 모음 ==========
	//void UseMoonlightGauge_Phase1();
	static void UseMoonlightGauge_Phase1();
};