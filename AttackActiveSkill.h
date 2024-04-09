#pragma once
#include "ActiveSkill.h"

class SkillObject;

// 공격형 스킬 (액티브)
class AttackActiveSkill final : public ActiveSkill
{
	friend class SkillManager;

private:
	static SkillObject* skillObject;	// [CHECK] 다른 스킬도 추가되면 static이 아니라 인스턴스 필드로 바꿔야 할수도

public:
	static void SetSkillObject(SkillObject& skillObject);

private:
	const Vec2 maxRange;	// 최대 이동범위 (넘어서면 자동으로 비활성화됨)
	const float speed;

	NO_CSTR_COPY_ASSIGN(AttackActiveSkill);
	AttackActiveSkill(const wstring& name, Vec2 maxRange, float speed=2.f);
	~AttackActiveSkill();

public:
	Vec2 GetMaxRange() const { return maxRange; }
	float GetSpeed() const { return speed; }

	virtual void OnKeyPressed(KEY_CODE keyCode) override;
	virtual void OnKeyDown(KEY_CODE keyCode) override {}
};

// 스킬 오브젝트 설정
inline void AttackActiveSkill::SetSkillObject(SkillObject& obj)
{
	if (skillObject == nullptr) skillObject = &obj;
}