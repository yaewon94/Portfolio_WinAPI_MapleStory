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
	// ========== ��ų �ݹ��Լ� ���� ==========
	void ExecuteAttackSkill(Skill& skill);
};