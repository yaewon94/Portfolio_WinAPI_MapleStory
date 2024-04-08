#pragma once

class SkillManager;
struct Skill;

// 스킬 콜백 선언
typedef void(SkillManager::* SKILL_CALLBACK)(Skill&);

// 스킬 구조체
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