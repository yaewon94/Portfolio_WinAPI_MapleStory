#pragma once
#include "ActiveSkill.h"

class SkillManager;

// �ݹ� �޼ҵ�
//typedef void(SkillManager::* SKILL_CALLBACK)();
typedef void(* SKILL_CALLBACK)(ActiveSkill*);

// (����x, ����x �� ��Ÿ ����) ��Ƽ�� ��ų Ŭ����
class ActiveEtcSkill final : public ActiveSkill
{
	friend class SkillManager;
	NO_CSTR_COPY_ASSIGN(ActiveEtcSkill);

private:
	SKILL_CALLBACK callback;

private:
	//ActiveEtcSkill(const wstring& name, SKILL_CALLBACK callback, void* params, ...);
	ActiveEtcSkill(const wstring& name, int Cost, SKILL_CALLBACK callback);
	~ActiveEtcSkill();

public:
	virtual void OnKeyPressed(KEY_CODE) override;
};