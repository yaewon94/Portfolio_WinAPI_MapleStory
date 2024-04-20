#pragma once

class SkillObject;

// ���ݽ�ų ������ ������ �ִ� Ŭ����
class AttackSkillModule
{
	friend class SkillManager;

private:
	float time = 0.f;			// ��ų ���� �� ����ð�

protected:
	const float Coefficient;	// �÷��̾� �ִ�ü�� ��� ���
	const float Delay;			// ��ų ���� ��, ��ų ������Ʈ�� Ȱ��ȭ �Ǳ���� �ɸ��� �ð�

	const float Duration;		// ��ų ������Ʈ Ȱ��ȭ �ð�

	const Vec2<float> MaxRange;	// �ִ� �̵����� (�Ѿ�� �ڵ����� ��Ȱ��ȭ��)
	const float Speed;			// ��ų ������Ʈ �̵� �ӵ�

protected:
	AttackSkillModule(float Coefficient, float Delay, float Duration, Vec2<float> MaxRange, float Speed);
	virtual ~AttackSkillModule();

public:
	float GetCoefficient() const { return Coefficient; }
	float GetDuration() const { return Duration; }
	Vec2<float> GetMaxRange() const { return MaxRange; }
	float GetSpeed() const { return Speed; }
};