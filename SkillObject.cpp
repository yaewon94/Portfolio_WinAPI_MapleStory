#include "PCH.h"
#include "SkillObject.h"

// 积己磊
SkillObject::SkillObject(const wstring& name, Vec2 offset, Vec2 scale, LAYER_TYPE layer)
	: GameObject(name, offset, scale, layer, false)
{
	if (layer == LAYER_TYPE::PLAYER_SKILL) {}
	else throw std::invalid_argument("invalid layer type");	// 按眉 积己 秒家
}

// 汗荤 积己磊
SkillObject::SkillObject(const SkillObject& origin) : GameObject(origin)
{
}

// 家戈磊
SkillObject::~SkillObject()
{
}