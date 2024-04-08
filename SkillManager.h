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
	// ========== ��ų �ݹ��Լ� ���� ==========
	static void ExecuteAttackSkill(Skill& skill);
};