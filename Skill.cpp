#include "PCH.h"
#include "Skill.h"

// static �ʵ� �ʱ�ȭ
UINT Skill::nextID = 0;

// ������
Skill::Skill(const wstring& name) : ID(nextID++), name(new wstring(name))
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