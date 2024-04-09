#include "PCH.h"
#include "AttackActiveSkill.h"

// 持失切
AttackActiveSkill::AttackActiveSkill(const wstring& name, Vec2 maxRange) 
	: ActiveSkill(name), maxRange(maxRange)
{
}

// 社瑚切
AttackActiveSkill::~AttackActiveSkill()
{
}