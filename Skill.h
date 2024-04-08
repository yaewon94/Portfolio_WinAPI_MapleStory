#pragma once

class SkillManager;
struct Skill;

// ��ų �ݹ� Ÿ�� ����
//typedef void(SkillManager::* SKILL_CALLBACK)(Skill&);	// SkillManager���� delete Skill��ü �� �� ��������
typedef void(* SKILL_CALLBACK)(Skill&);	// SkillManager�� static �Լ� ȣ���� ��

// ��ų
struct Skill
{
	friend class SkillManager;

private:
	static UINT nextID;

private:
	const UINT ID;
	wstring name;
	SKILL_CALLBACK callback;

	NO_CSTR_COPY_ASSIGN(Skill);
	Skill(const wstring& name, SKILL_CALLBACK callback);
	~Skill();
};