#pragma once
#include "ActiveSkill.h"

class SkillManager;

// �ݹ� �޼ҵ�
//typedef void(SkillManager::* SKILL_CALLBACK)();
typedef void(* SKILL_CALLBACK)(void);

// (����x, ����x �� ��Ÿ ����) ��Ƽ�� ��ų Ŭ����
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