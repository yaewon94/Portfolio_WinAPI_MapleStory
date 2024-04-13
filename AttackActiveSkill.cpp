#include "PCH.h"
#include "AttackActiveSkill.h"
#include "SkillManager.h"
#include "FSM.h"
#include "LevelManager.h"
#include "SkillObject.h"

// ������
AttackActiveSkill::AttackActiveSkill(const wstring& name, Vec2<float> maxRange, float speed) 
	: ActiveSkill(name), maxRange(maxRange), speed(speed), skillObject(nullptr)
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

	skillObject->GetParent()->GetComponent<FSM>()->ChangeState(OBJECT_STATE::ATTACK);
	skillObject->SetSkill(*this);

	// ������ �ð� ����, ��ų ������Ʈ Ȱ��ȭ
	SkillManager::GetInstance().LaunchSkill(*this);
}