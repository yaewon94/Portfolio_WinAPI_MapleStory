#include "PCH.h"
#include "AttackSkillModule.h"

// 持失切
AttackSkillModule::AttackSkillModule(float Coefficient, float Delay, float Duration, Vec2<float> MaxRange, float Speed)
	: Coefficient(Coefficient), Delay(Delay), Duration(Duration)
	, MaxRange(MaxRange), Speed(Speed)
	, skillObject(nullptr)
{
}

// 社瑚切
AttackSkillModule::~AttackSkillModule()
{
	skillObject = nullptr;
}