#include "PCH.h"
#include "Component.h"
#include "GameObject.h"

// ������
Component::Component(GameObject& owner) : owner(&owner)
{
}

// ���� ������
Component::Component(const Component& origin) : Entity(origin)
{
	owner = origin.owner->Clone();
}

// �Ҹ���
Component::~Component()
{
	// GameObject* �� ����Ű�� ���� Level���� �����Ұ���
}