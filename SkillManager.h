#pragma once

struct Skill;

class SkillManager final
{
	SINGLETON(SkillManager);

private:
	vector<Skill*> skills;

public:
	void Init();

	Skill& GetSkill(size_t index) { return *skills.at(index); }

private:
	// ========== 스킬 콜백함수 모음 ==========
	static void ExecuteAttackSkill(Skill& skill);
};