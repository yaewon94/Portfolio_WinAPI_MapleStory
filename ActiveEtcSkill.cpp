#include "PCH.h"
#include "ActiveEtcSkill.h"
#include "SkillManager.h"
#include "Player.h"

// ������
ActiveEtcSkill::ActiveEtcSkill(const wstring& name, int Cost, SKILL_CALLBACK callback)
	: ActiveSkill(name, Cost), callback(callback)
{
}

// �Ҹ���
ActiveEtcSkill::~ActiveEtcSkill()
{
	callback = nullptr;
}

// [event] Ű �Է� �� ȣ��
void ActiveEtcSkill::OnKeyPressed(KEY_CODE)
{
	// ��ų ��뿡 �ʿ��� �ڽ�Ʈ�� Ȯ��
	if (GetPlayer().GetCurrentSkillCost() < Cost) return;

	// �ڽ�Ʈ �Ҹ�
	GetPlayer().UseSkillCost(Cost);
	// �ݹ� ȣ��
	//(SkillManager::GetInstance().*(callback))();
	callback();
}