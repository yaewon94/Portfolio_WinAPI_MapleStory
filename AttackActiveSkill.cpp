#include "PCH.h"
#include "AttackActiveSkill.h"
#include "LevelManager.h"
#include "SkillObject.h"

// static �ʵ� �ʱ�ȭ
SkillObject* AttackActiveSkill::skillObject = nullptr;

// ������
AttackActiveSkill::AttackActiveSkill(const wstring& name, Vec2 maxRange, float speed) 
	: ActiveSkill(name), maxRange(maxRange), speed(speed)
{
}

// �Ҹ���
AttackActiveSkill::~AttackActiveSkill()
{
}

// Ű ������ �� ȣ��
void AttackActiveSkill::OnKeyPressed(KEY_CODE keyCode)
{
	if (skillObject->IsActive()) return;

	skillObject->SetSkill(*this);
	skillObject->SetActive(true);
}