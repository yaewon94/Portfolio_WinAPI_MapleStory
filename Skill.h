#pragma once
#include "Entity.h"

//class Skill;
//class SkillManager;

// 스킬 콜백 타입 선언
//typedef void(SkillManager::* SKILL_CALLBACK)(Skill&);	// SkillManager에서 delete Skill객체 할 때 문제생김
//typedef void(* SKILL_CALLBACK)(Skill&);	// SkillManager의 static 함수 호출할 것

// 모든 스킬 타입의 상위 클래스
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