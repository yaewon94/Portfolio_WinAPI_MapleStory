#include "PCH.h"
#include "AttackActiveSkill.h"

// ������
AttackActiveSkill::AttackActiveSkill(const wstring& name, Vec2 maxRange) 
	: ActiveSkill(name), maxRange(maxRange)
{
}

// �Ҹ���
AttackActiveSkill::~AttackActiveSkill()
{
}