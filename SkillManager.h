#pragma once
#include "ActiveSkill.h"

class Skill;
class PlayerAttackSkill;

// 스킬 관리 클래스
class SkillManager final
{
	SINGLETON(SkillManager);

private:
	vector<Skill*> skills;
	list<PlayerAttackSkill*> reservedSkills;	 // 딜레이 타임이 있는 스킬들 스킬오브젝트 활성화 준비용도

public:
	void Init();
	void Tick();

	Skill& GetSkill(size_t index) { return *skills.at(index); }
	void LaunchSkill(PlayerAttackSkill& skill) { reservedSkills.push_back(&skill); }
	void SetValid(ActiveSkill* skill, bool flag) { skill->isValid = flag; }

private:
	// ========== 스킬 콜백함수 모음 ==========
	//void UseMoonlightGauge_Phase1();
	static void UseMoonlightGauge_Phase1();
};