#include "PCH.h"
#include "ActiveSkill.h"

// static �ʵ� �ʱ�ȭ
Player* ActiveSkill::player = nullptr;

// ������
ActiveSkill::ActiveSkill(const wstring& name, int Cost)
	: Skill(name), Cost(Cost)
{
}

// �Ҹ���
ActiveSkill::~ActiveSkill()
{
}