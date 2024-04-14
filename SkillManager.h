#pragma once

class Skill;
class AttackActiveSkill;

class SkillManager final
{
	SINGLETON(SkillManager);

private:
	vector<Skill*> skills;
	list<AttackActiveSkill*> reservedSkills;	 // ������ Ÿ���� �ִ� ��ų�� ��ų������Ʈ Ȱ��ȭ �غ�뵵

public:
	void Init();
	void Tick();

	Skill& GetSkill(size_t index) { return *skills.at(index); }
	void LaunchSkill(AttackActiveSkill& skill) { reservedSkills.push_back(&skill); }

private:
	// ========== ��ų �ݹ��Լ� ���� ==========
	//static void ExecuteAttackSkill(Skill& skill);
};