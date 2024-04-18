#include "PCH.h"
#include "AttackSkillModule.h"

// ������
AttackSkillModule::AttackSkillModule(float Coefficient, float Delay, float Duration, Vec2<float> MaxRange, float Speed)
	: Coefficient(Coefficient), Delay(Delay), Duration(Duration)
	, MaxRange(MaxRange), Speed(Speed)
	, skillObject(nullptr)
{
}

// �Ҹ���
AttackSkillModule::~AttackSkillModule()
{
	skillObject = nullptr;
}