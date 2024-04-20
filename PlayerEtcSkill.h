#pragma once
#include "ActiveSkill.h"

class SkillManager;

// 콜백 메소드
//typedef void(SkillManager::* SKILL_CALLBACK)();
typedef void(* SKILL_CALLBACK)(void);

// (공격x, 버프x 인 기타 종류) 액티브 스킬 클래스
class PlayerEtcSkill final : public ActiveSkill
{
	friend class SkillManager;
	NO_CSTR_COPY_ASSIGN(PlayerEtcSkill);

private:
	SKILL_CALLBACK callback;

private:
	//PlayerEtcSkill(const wstring& name, SKILL_CALLBACK callback, void* params, ...);
	PlayerEtcSkill(const wstring& name, int Cost, SKILL_CALLBACK callback);
	~PlayerEtcSkill();

public:
	virtual void OnKeyPressed(KEY_CODE) override;

private:
	virtual void UseSkill(GameObject* caster, SkillObject* skillObj) override {}
};