#pragma once

class Skill;
class AttackActiveSkill;

class SkillManager final
{
	SINGLETON(SkillManager);

private:
	vector<Skill*> skills;
	list<AttackActiveSkill*> reservedSkills;	 // 딜레이 타임이 있는 스킬들 스킬오브젝트 활성화 준비용도

public:
	void Init();
	void Tick();

	Skill& GetSkill(size_t index) { return *skills.at(index); }
	void LaunchSkill(AttackActiveSkill& skill) { reservedSkills.push_back(&skill); }

private:
	// ========== 스킬 콜백함수 모음 ==========
	//static void ExecuteAttackSkill(Skill& skill);
};