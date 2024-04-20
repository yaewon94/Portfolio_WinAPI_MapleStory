#pragma once
#include "Entity.h"

class GameObject;
class SkillObject;
//class Skill;
//class SkillManager;

// 스킬 콜백 타입 선언
//typedef void(SkillManager::* SKILL_CALLBACK)(Skill&);	// SkillManager에서 delete Skill객체 할 때 문제생김
//typedef void(* SKILL_CALLBACK)(Skill&);	// SkillManager의 static 함수 호출할 것

// 모든 스킬 타입의 상위 클래스
// 추상클래스는 아니지만 접근제한자 때문에 외부에서 생성 불가
class Skill : public Entity
{
	friend class SkillManager;
	NO_CSTR_COPY_ASSIGN(Skill);

private:
	wstring name;
	OBJECT_STATE state = OBJECT_STATE::NONE;	// 상태전환 or 애니메이션 전환에 이용
	//SKILL_CALLBACK callback;

protected:
	//Skill(const wstring& name, SKILL_CALLBACK callback);
	Skill(const wstring& name);
	~Skill();

protected:
	OBJECT_STATE GetObjectState() const { return state; }

private:
	void SetObjectState(OBJECT_STATE state) { this->state = state; }

public:
	const wstring& GetName() { return name; }

public:
	virtual void UseSkill(GameObject* caster, SkillObject* skillObj) = 0;
};