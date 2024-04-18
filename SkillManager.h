#pragma once
#include "ActiveSkill.h"

class Skill;
class AttackActiveSkill;

// ��ų ���� Ŭ����
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
	void SetValid(ActiveSkill* skill, bool flag) { skill->isValid = flag; }

private:
	// ========== ��ų �ݹ��Լ� ���� ==========
	//void UseMoonlightGauge_Phase1();
	static void UseMoonlightGauge_Phase1(ActiveSkill* skill);
};