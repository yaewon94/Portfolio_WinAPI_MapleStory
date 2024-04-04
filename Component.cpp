#include "PCH.h"
#include "Component.h"
#include "GameObject.h"

// 생성자
Component::Component(GameObject& owner) : owner(&owner)
{
}

// 복사 생성자
Component::Component(const Component& origin) : Entity(origin)
{
	owner = origin.owner->Clone();
}

// 소멸자
Component::~Component()
{
	// GameObject* 가 가리키는 것은 Level에서 삭제할거임
}