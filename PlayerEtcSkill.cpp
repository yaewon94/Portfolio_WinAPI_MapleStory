#include "PCH.h"
#include "PlayerEtcSkill.h"
#include "SkillManager.h"
#include "Player.h"

// 생성자
PlayerEtcSkill::PlayerEtcSkill(const wstring& name, int Cost, SKILL_CALLBACK callback)
	: ActiveSkill(name, Cost), callback(callback)
{
}

// 소멸자
PlayerEtcSkill::~PlayerEtcSkill()
{
	callback = nullptr;
}

// [event] 키 입력 시 호출
void PlayerEtcSkill::OnKeyPressed(KEY_CODE)
{
	if (IsValid())
	{
		// 스킬 사용에 필요한 코스트량 확인
		if (GetPlayer().GetCurrentSkillCost() < Cost) return;

		// 코스트 소모
		GetPlayer().UseSkillCost(Cost);
		// 콜백 호출
		//(SkillManager::GetInstance().*(callback))();
		callback();
	}
}