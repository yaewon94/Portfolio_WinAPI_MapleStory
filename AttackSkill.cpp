#include "PCH.h"
#include "AttackSkill.h"

// ������
AttackActiveSkill::AttackActiveSkill(const wstring& name, KEY_CODE keyCode, Vec2 maxRange) 
	: ActiveSkill(name, keyCode)
{
}

// �Ҹ���
AttackActiveSkill::~AttackActiveSkill()
{
}