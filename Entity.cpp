#include "PCH.h"
#include "Entity.h"

// static 멤버 정의
UINT Entity::nextID = 0;

// 생성자
Entity::Entity(const wstring& name) : ID(nextID++), name(name)
{
}

// 복사 생성자
Entity::Entity(const Entity& origin) : ID(nextID++), name(origin.name)
{
}

// 소멸자
Entity::~Entity()
{
}
