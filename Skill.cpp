#include "PCH.h"
#include "Skill.h"

// ������
Skill::Skill(const wstring& name) : name(name), caster(nullptr)
{
}

// �Ҹ���
Skill::~Skill()
{
	caster = nullptr;
}