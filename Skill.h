#pragma once
#include "Entity.h"

//class Skill;
//class SkillManager;

// ��ų �ݹ� Ÿ�� ����
//typedef void(SkillManager::* SKILL_CALLBACK)(Skill&);	// SkillManager���� delete Skill��ü �� �� ��������
//typedef void(* SKILL_CALLBACK)(Skill&);	// SkillManager�� static �Լ� ȣ���� ��

// ��� ��ų Ÿ���� ���� Ŭ����
// [abstract class]
class Skill : public Entity
{
	friend class SkillManager;
	NO_CSTR_COPY_ASSIGN(Skill);

protected:
	wstring name;
	//SKILL_CALLBACK callback;

	//Skill(const wstring& name, SKILL_CALLBACK callback);
	Skill(const wstring& name);
	~Skill();
};