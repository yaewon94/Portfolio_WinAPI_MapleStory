#pragma once

class SkillManager;
struct Skill;

// ��ų �ݹ� ����
typedef void(SkillManager::* SKILL_CALLBACK)(Skill&);

// ��ų ����ü
struct Skill
{
	friend class SkillManager;

private:
	static UINT nextID;

private:
	const UINT ID;
	wstring* name;
	SKILL_CALLBACK callback;

	NO_CSTR_COPY_ASSIGN(Skill);
	Skill(const wstring& name, SKILL_CALLBACK callback);
	~Skill();
};