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
	// TODO : ����ó�� ���� ���·� �Ǵ��ؼ� ���ݰ��� ���� üũ�ϴ°ɷ� ����
	SkillObject* skillObj = (SkillObject*)GetPlayer().GetChild(LAYER_TYPE::PLAYER_SKILL);

	// �ߵ� ���� üũ
	if (skillObj->IsActive()) return;
	if (!canWithJump && !GetPlayer().CanJump()) return;

	// ���� ����, ��ų ������Ʈ�� ���� ��ų ����
	GetPlayer().GetComponent<FSM>()->ChangeState(OBJECT_STATE::ATTACK);
	skillObj->SetSkill(*this);

	// ������ �ð� ����, ��ų ������Ʈ Ȱ��ȭ
	SkillManager::GetInstance().LaunchSkill(this, skillObj);
}