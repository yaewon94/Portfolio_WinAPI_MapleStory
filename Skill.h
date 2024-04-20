#pragma once
#include "Entity.h"

class GameObject;
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
	GameObject* caster;	// ��ų ������
	//SKILL_CALLBACK callback;

protected:
	//Skill(const wstring& name, SKILL_CALLBACK callback);
	Skill(const wstring& name);
	~Skill();

protected:
	OBJECT_STATE GetObjectState() const { return state; }
	GameObject& GetCaster() { return *caster; }

private:
	void SetObjectState(OBJECT_STATE state) { this->state = state; }

public:
	const wstring& GetName() { return name; }
	void SetSkillCaster(GameObject* caster) { this->caster = caster; }

public:
	virtual void UseSkill() = 0;
};