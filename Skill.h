#pragma once
#include "Entity.h"

class Animation;
class GameObject;
class SkillObject;
//class Skill;
//class SkillManager;

// ��ų �ݹ� Ÿ�� ����
//typedef void(SkillManager::* SKILL_CALLBACK)(Skill&);	// SkillManager���� delete Skill��ü �� �� ��������
//typedef void(* SKILL_CALLBACK)(Skill&);	// SkillManager�� static �Լ� ȣ���� ��
typedef void(*ON_DISAPPEAR_CALLBACK)(GameObject*);	// ��ų������Ʈ ��Ȱ��ȭ�ɶ� �ݹ�

// ��� ��ų Ÿ���� ���� Ŭ����
// �߻�Ŭ������ �ƴ����� ���������� ������ �ܺο��� ���� �Ұ�
class Skill : public Entity
{
	friend class SkillManager;
	NO_CSTR_COPY_ASSIGN(Skill);

private:
	int index = -1;
	wstring name;
	OBJECT_STATE state = OBJECT_STATE::DEFAULT;	// ������ȯ or �ִϸ��̼� ��ȯ�� �̿�
	map<OBJECT_STATE, Animation*> animMap;		// ��ų������Ʈ �ִϸ��̼� �����
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