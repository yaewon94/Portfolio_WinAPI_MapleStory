#pragma once
#include "Entity.h"

class Animation;
class GameObject;
class SkillObject;
//class Skill;
//class SkillManager;

// 스킬 콜백 타입 선언
//typedef void(SkillManager::* SKILL_CALLBACK)(Skill&);	// SkillManager에서 delete Skill객체 할 때 문제생김
//typedef void(* SKILL_CALLBACK)(Skill&);	// SkillManager의 static 함수 호출할 것
typedef void(*ON_DISAPPEAR_CALLBACK)(GameObject*);	// 스킬오브젝트 비활성화될때 콜백

// 모든 스킬 타입의 상위 클래스
// 추상클래스는 아니지만 접근제한자 때문에 외부에서 생성 불가
class Skill : public Entity
{
	friend class SkillManager;
	NO_CSTR_COPY_ASSIGN(Skill);

private:
	int index = -1;
	wstring name;
	OBJECT_STATE state = OBJECT_STATE::DEFAULT;	// 상태전환 or 애니메이션 전환에 이용
	map<OBJECT_STATE, Animation*> animMap;		// 스킬오브젝트 애니메이션 재생용
	//SKILL_CALLBACK callback;

	ON_DISAPPEAR_CALLBACK on_disappear = nullptr;
	

protected:
	//Skill(const wstring& name, SKILL_CALLBACK callback);
	Skill(const wstring& name);
	~Skill();

private:
	void SetObjectState(OBJECT_STATE state) { this->state = state; }

public:
	int GetIndex() { return index; }
	const wstring& GetName() { return name; }
	OBJECT_STATE GetObjectState() const { return state; }
	map<OBJECT_STATE, Animation*>& GetAnimationMap() { return animMap; }

	void OnDisappear(GameObject* obj);

public:
	virtual void UseSkill(GameObject* caster, SkillObject* skillObj) = 0;
};