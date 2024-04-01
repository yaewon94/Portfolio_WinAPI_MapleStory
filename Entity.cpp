#include "PCH.h"
#include "Entity.h"

// static ��� ����
UINT Entity::nextID = 0;

// ������
Entity::Entity() : ID(nextID++)
{
}

// ���� ������
Entity::Entity(const Entity& origin) : ID(nextID++)
{
}

// �̵� ������
Entity::Entity(Entity&& origin) noexcept : ID(0)
{
    *this = std::move(origin);
}

// (����)���� ������
Entity& Entity::operator=(const Entity& origin)
{
    // �̹� ������ Entity��ü�� �����ϴ� ���̱� ������ this->ID�� �״�� �д�
    return *this;
}

// �̵����� ������
Entity& Entity::operator=(Entity&& origin) noexcept
{
    // [check] �̹� ������ Entity��ü�� origin.ID���� �־���� �ϴµ� const UINT�� ���ٲ�
    //ID = origin.ID;
    //origin.ID = 0;
    UINT* pID = const_cast<UINT*>(&ID);
    *pID = origin.ID;
    pID = const_cast<UINT*>(&origin.ID);
    *pID = 0;

    return *this;
}

// �Ҹ���
Entity::~Entity()
{
}
