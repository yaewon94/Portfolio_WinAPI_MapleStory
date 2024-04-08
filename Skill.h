#pragma once

class SkillManager;
struct Skill;

// 스킬 콜백 타입 선언
//typedef void(SkillManager::* SKILL_CALLBACK)(Skill&);	// SkillManager에서 delete Skill객체 할 때 문제생김
typedef void(* SKILL_CALLBACK)(Skill&);	// SkillManager의 static 함수 호출할 것

// 스킬
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