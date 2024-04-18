#pragma once

class SkillObject;

// 공격스킬 정보를 가지고 있는 클래스
class AttackSkillModule
{
	friend class SkillManager;

private:
	const float Coefficient;	// 플레이어 최대체력 비례 계수
	const float Delay;			// 스킬 시전 후, 스킬 오브젝트가 활성화 되기까지 걸리는 시간

	const float Duration;		// 스킬 오브젝트 활성화 시간

	const Vec2<float> MaxRange;	// 최대 이동범위 (넘어서면 자동으로 비활성화됨)
	const float Speed;			// 스킬 오브젝트 이동 속도

private:
	SkillObject* skillObject;
	float time = 0.f;			// 스킬 시전 후 경과시간

protected:
	AttackSkillModule(float Coefficient, float Delay, float Duration, Vec2<float> MaxRange, float Speed);
	~AttackSkillModule();

protected:
	SkillObject& GetSkillObject() { assert(skillObject); return *skillObject; }

public:
	float GetCoefficient() const { return Coefficient; }
	Vec2<float> GetMaxRange() const { return MaxRange; }
	float GetSpeed() const { return Speed; }
	void SetSkillObject(SkillObject& skillObject) { this->skillObject = &skillObject; }
};