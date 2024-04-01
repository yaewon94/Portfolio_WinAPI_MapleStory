#include "PCH.h"
#include "Component.h"
#include "GameObject.h"

// 생성자
Component::Component(GameObject& owner) : owner(nullptr)
{
	this->owner = &owner;
}

// 복사 생성자
Component::Component(const Component& origin) : Entity(origin), owner(nullptr)
{
	owner = new GameObject(*(origin.owner));
}

// 이동 생성자
Component::Component(Component&& origin) noexcept : Entity(std::move(origin))
{
	*this = std::move(origin);
}

// 소멸자
Component::~Component()
{
	// GameObject* 가 가리키는 것 삭제하면 안됨
}

// 대입 연산자
Component& Component::operator=(const Component& origin)
{
	owner = new GameObject(*origin.owner);

	return *this;
}

// 이동 대입 연산자
Component& Component::operator=(Component&& origin) noexcept
{
	if (this != &origin)
	{
		//owner->Destroy(); // !!없애면 안됨
		owner = origin.owner;
		origin.owner = nullptr;
	}
	this;

	return *this;
}
