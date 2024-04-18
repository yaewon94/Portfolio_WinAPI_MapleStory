#pragma once

class SkillObject;

// ���ݽ�ų ������ ������ �ִ� Ŭ����
class AttackSkillModule
{
	friend class SkillManager;

private:
	const float Coefficient;	// �÷��̾� �ִ�ü�� ��� ���
	const float Delay;			// ��ų ���� ��, ��ų ������Ʈ�� Ȱ��ȭ �Ǳ���� �ɸ��� �ð�

	const float Duration;		// ��ų ������Ʈ Ȱ��ȭ �ð�

	const Vec2<float> MaxRange;	// �ִ� �̵����� (�Ѿ�� �ڵ����� ��Ȱ��ȭ��)
	const float Speed;			// ��ų ������Ʈ �̵� �ӵ�

private:
	SkillObject* skillObject;
	float time = 0.f;			// ��ų ���� �� ����ð�

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