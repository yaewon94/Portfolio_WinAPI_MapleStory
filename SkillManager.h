#pragma once
#include "ActiveSkill.h"

class AttackSkillModule;
class GameObject;
class Skill;
class PlayerAttackSkill;

// ��ų ���� Ŭ����
class SkillManager final
{
	SINGLETON(SkillManager);

private:
	vector<Skill*> skills;
	list<std::pair<AttackSkillModule*, GameObject*>> reservedSkills;	 // ������ Ÿ���� �ִ� ��ų�� ��ų������Ʈ Ȱ��ȭ �غ�뵵

public:
	void Init();
	void Tick();

	Skill& GetSkill(size_t index) { return *skills.at(index); }
	void LaunchSkill(AttackSkillModule* skill, GameObject* skillObj) { reservedSkills.push_back(make_pair(skill, skillObj)); }
	void SetValid(ActiveSkill* skill, bool flag) { skill->isValid = flag; }

private:
	// ========== ��ų �ݹ��Լ� ���� ==========
	//void UseMoonlightGauge_Phase1();
	static void UseMoonlightGauge_Phase1();
};