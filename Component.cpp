#include "PCH.h"
#include "Component.h"
#include "GameObject.h"

// 생성자
Component::Component() : owner(nullptr)
{
}

Component::Component(GameObject& owner) : owner(&owner)
{
}

// 복사 생성자
Component::Component(const Component& origin) : Entity(origin), owner(nullptr)
{
	// ERROR : 또 다시 게임오브젝트의 복사생성자를 호출하게 되서 무한반복됨
	//owner = origin.owner->Clone();
}

// 소멸자
Component::~Component()
{
	// GameObject* 가 가리키는 것은 Level에서 삭제할거임
	owner = nullptr;
}