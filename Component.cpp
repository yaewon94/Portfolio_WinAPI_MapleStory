#include "PCH.h"
#include "Component.h"
#include "GameObject.h"

// ������
Component::Component(GameObject& owner) : owner(nullptr)
{
	this->owner = &owner;
}

// ���� ������
Component::Component(const Component& origin) : Entity(origin), owner(nullptr)
{
	owner = new GameObject(*(origin.owner));
}

// �̵� ������
Component::Component(Component&& origin) noexcept : Entity(std::move(origin))
{
	*this = std::move(origin);
}

// �Ҹ���
Component::~Component()
{
	// GameObject* �� ����Ű�� �� �����ϸ� �ȵ�
}

// ���� ������
Component& Component::operator=(const Component& origin)
{
	owner = new GameObject(*origin.owner);

	return *this;
}

// �̵� ���� ������
Component& Component::operator=(Component&& origin) noexcept
{
	if (this != &origin)
	{
		//owner->Destroy(); // !!���ָ� �ȵ�
		owner = origin.owner;
		origin.owner = nullptr;
	}
	this;

	return *this;
}
