#include "PCH.h"
#include "Entity.h"

// static ��� ����
UINT Entity::nextID = 0;

// ������
Entity::Entity() : ID(nextID++)
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
