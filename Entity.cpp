#include "PCH.h"
#include "Entity.h"

// static 멤버 정의
UINT Entity::nextID = 0;

// 생성자
Entity::Entity() : ID(nextID++)
{
}

// 복사 생성자
Entity::Entity(const Entity& origin) : ID(nextID++)
{
}

// 이동 생성자
Entity::Entity(Entity&& origin) noexcept : ID(0)
{
    *this = std::move(origin);
}

// (복사)대입 연산자
Entity& Entity::operator=(const Entity& origin)
{
    // 이미 생성된 Entity객체에 대입하는 것이기 때문에 this->ID는 그대로 둔다
    return *this;
}

// 이동대입 연산자
Entity& Entity::operator=(Entity&& origin) noexcept
{
    // [check] 이미 생성된 Entity객체에 origin.ID값을 넣어줘야 하는데 const UINT라 못바꿈
    //ID = origin.ID;
    //origin.ID = 0;
    UINT* pID = const_cast<UINT*>(&ID);
    *pID = origin.ID;
    pID = const_cast<UINT*>(&origin.ID);
    *pID = 0;

    return *this;
}

// 소멸자
Entity::~Entity()
{
}
