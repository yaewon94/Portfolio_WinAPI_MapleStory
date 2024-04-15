#pragma once
#include "ActiveSkill.h"

class SkillObject;

// 공격형 스킬 (액티브)
class AttackActiveSkill final : public ActiveSkill
{
	friend class SkillManager;

private:
	SkillObject* skillObject;
	Vec2 maxRange;	// 최대 이동범위 (넘어서면 자동으로 비활성화됨)
	float speed;		// 스킬 오브젝트 이동 속도

	const float Delay = DEFAULT_ANIM_DURATION * 2;	// 키 입력 후, 스킬 오브젝트가 활성화 되기까지 걸리는 시간
	float time = 0.f;		// 스킬 시전 후 경과시간

	bool canWithJump;		// 점프 공격 가능 여부

	NO_CSTR_COPY_ASSIGN(AttackActiveSkill);
	AttackActiveSkill(const wstring& name, Vec2 maxRange, float speed=2.f, bool canWithJump=false);
	~AttackActiveSkill();

public:
	Vec2 GetMaxRange() const { return maxRange; }
	float GetSpeed() const { return speed; }
	void SetSkillObject(SkillObject& skillObject);

	virtual void OnKeyPressed(KEY_CODE keyCode) override;
};

// 스킬 오브젝트 설정
inline void AttackActiveSkill::SetSkillObject(SkillObject& obj)
{
	if (skillObject == nullptr) skillObject = &obj;
}