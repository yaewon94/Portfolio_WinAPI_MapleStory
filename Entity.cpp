#include "PCH.h"
#include "Entity.h"

// static ��� ����
UINT Entity::nextID = 0;

// ������
Entity::Entity(const wstring& name) : ID(nextID++), name(name)
{
}

// ���� ������
Entity::Entity(const Entity& origin) : ID(nextID++), name(origin.name)
{
}

// �Ҹ���
Entity::~Entity()
{
}
