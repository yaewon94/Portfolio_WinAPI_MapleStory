#pragma once
#include "Entity.h"

class GameObject;
class SkillObject;
//class Skill;
//class SkillManager;

// ��ų �ݹ� Ÿ�� ����
//typedef void(SkillManager::* SKILL_CALLBACK)(Skill&);	// SkillManager���� delete Skill��ü �� �� ��������
//typedef void(* SKILL_CALLBACK)(Skill&);	// SkillManager�� static �Լ� ȣ���� ��

// ��� ��ų Ÿ���� ���� Ŭ����
// �߻�Ŭ������ �ƴ����� ���������� ������ �ܺο��� ���� �Ұ�
class Skill : public Entity
{
	friend class SkillManager;
	NO_CSTR_COPY_ASSIGN(Skill);

private:
	wstring name;
	OBJECT_STATE state = OBJECT_STATE::NONE;	// ������ȯ or �ִϸ��̼� ��ȯ�� �̿�
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