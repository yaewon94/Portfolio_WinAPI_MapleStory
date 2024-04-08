#include "PCH.h"
#include "Skill.h"

// static �ʵ� �ʱ�ȭ
UINT Skill::nextID = 0;

// ������
Skill::Skill(const wstring& name, SKILL_CALLBACK callback) 
	: ID(nextID++), name(new wstring(name)), callback(callback)
{
}

// �Ҹ���
Skill::~Skill()
{
	if (name != nullptr)
	{
		delete name;
		name = nullptr;
	}
}