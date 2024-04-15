#include "PCH.h"
#include "AttackActiveSkill.h"
#include "SkillManager.h"
#include "FSM.h"
#include "LevelManager.h"
#include "Player.h"
#include "SkillObject.h"

// ������
AttackActiveSkill::AttackActiveSkill(const wstring& name, Vec2 maxRange, float speed, bool canWithJump) 
	: ActiveSkill(name), maxRange(maxRange), speed(speed), canWithJump(canWithJump)
	, skillObject(nullptr)
{
}

// �Ҹ���
AttackActiveSkill::~AttackActiveSkill()
{
}

// Ű ������ �� ȣ��
void AttackActiveSkill::OnKeyPressed(KEY_CODE keyCode)
{
	// �ߵ� ���� üũ
	if (skillObject->IsActive()) return;
	if (!canWithJump && !GetPlayer().CanJump()) return;

	// ���� ����, ��ų ������Ʈ�� ���� ��ų ����
	GetPlayer().GetComponent<FSM>()->ChangeState(OBJECT_STATE::ATTACK);
	skillObject->SetSkill(*this);

	// ������ �ð� ����, ��ų ������Ʈ Ȱ��ȭ
	SkillManager::GetInstance().LaunchSkill(*this);
}