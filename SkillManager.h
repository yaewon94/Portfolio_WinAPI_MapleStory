#pragma once

struct Skill;

class SkillManager final
{
	SINGLETON(SkillManager);

private:
	vector<Skill*> skills;

public:
	void Init();

private:
	// ========== 스킬 콜백함수 모음 ==========
	void ExecuteAttackSkill(Skill& skill);
};