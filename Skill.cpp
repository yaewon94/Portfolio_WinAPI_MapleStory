#include "PCH.h"
#include "Skill.h"

// ������
/*
Skill::Skill(const wstring& name, SKILL_CALLBACK callback) 
	: ID(nextID++), name(name), callback(callback)
{
}
*/

Skill::Skill(const wstring& name) : name(name)
{
}

// �Ҹ���
Skill::~Skill()
{
}