#include "PCH.h"
#include "PlayerEtcSkill.h"
#include "SkillManager.h"
#include "Player.h"

// ������
PlayerEtcSkill::PlayerEtcSkill(const wstring& name, int Cost, SKILL_CALLBACK callback)
	: ActiveSkill(name, Cost), callback(callback)
{
}

// �Ҹ���
PlayerEtcSkill::~PlayerEtcSkill()
{
	callback = nullptr;
}

// [event] Ű �Է� �� ȣ��
void PlayerEtcSkill::OnKeyPressed(KEY_CODE)
{
	if (IsValid())
	{
		// ��ų ��뿡 �ʿ��� �ڽ�Ʈ�� Ȯ��
		if (GetPlayer().GetCurrentSkillCost() < Cost) return;

		// �ڽ�Ʈ �Ҹ�
		GetPlayer().UseSkillCost(Cost);
		// �ݹ� ȣ��
		//(SkillManager::GetInstance().*(callback))();
		callback();
	}
}