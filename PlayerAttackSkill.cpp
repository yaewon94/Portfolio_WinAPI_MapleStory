#include "PCH.h"
#include "PlayerAttackSkill.h"
#include "SkillManager.h"
#include "FSM.h"
#include "LevelManager.h"
#include "Player.h"
#include "SkillObject.h"

// ������
PlayerAttackSkill::PlayerAttackSkill(const wstring& name, float Coefficient, float Delay, float Duration, Vec2<float> MaxRange, float Speed, int Cost) 
	: ActiveSkill(name, Cost)
	, AttackSkillModule(Coefficient, Delay, Duration, MaxRange, Speed)
{
}

// �Ҹ���
PlayerAttackSkill::~PlayerAttackSkill()
{
}

// Ű ������ �� ȣ��
void PlayerAttackSkill::OnKeyPressed(KEY_CODE keyCode)
{
	// �ߵ� ���� üũ
	if (GetSkillObject().IsActive()) return;
	if (!canWithJump && !GetPlayer().CanJump()) return;

	// ���� ����, ��ų ������Ʈ�� ���� ��ų ����
	GetPlayer().GetComponent<FSM>()->ChangeState(OBJECT_STATE::ATTACK);
	GetSkillObject().SetSkill(*this);

	// ������ �ð� ����, ��ų ������Ʈ Ȱ��ȭ
	SkillManager::GetInstance().LaunchSkill(*this);
}