#include "PCH.h"
#include "SkillObject.h"

// ������
SkillObject::SkillObject(const wstring& name, Vec2 offset, Vec2 scale, LAYER_TYPE layer)
	: GameObject(name, offset, scale, layer, false)
{
	if (layer == LAYER_TYPE::PLAYER_SKILL) {}
	else throw std::invalid_argument("invalid layer type");	// ��ü ���� ���
}

// ���� ������
SkillObject::SkillObject(const SkillObject& origin) : GameObject(origin)
{
}

// �Ҹ���
SkillObject::~SkillObject()
{
}