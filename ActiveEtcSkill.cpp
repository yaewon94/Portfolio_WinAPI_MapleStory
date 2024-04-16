#include "PCH.h"
#include "ActiveEtcSkill.h"
#include "SkillManager.h"
#include "Player.h"

// 생성자
ActiveEtcSkill::ActiveEtcSkill(const wstring& name, int Cost, SKILL_CALLBACK callback)
	: ActiveSkill(name, Cost), callback(callback)
{
}

// 소멸자
ActiveEtcSkill::~ActiveEtcSkill()
{
	callback = nullptr;
}

// [event] 키 입력 시 호출
void ActiveEtcSkill::OnKeyPressed(KEY_CODE)
{
	// 스킬 사용에 필요한 코스트량 확인
	if (GetPlayer().GetCurrentSkillCost() < Cost) return;

	// 코스트 소모
	GetPlayer().UseSkillCost(Cost);
	// 콜백 호출
	//(SkillManager::GetInstance().*(callback))();
	callback();
}