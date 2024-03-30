#include "PCH.h"
#include "Component.h"
#include "GameObject.h"

// ������
Component::Component(GameObject* owner) : owner(owner)
{
}

// ���� ������
Component::Component(const Component& origin) : Entity(origin), owner(nullptr)
{
	owner = new GameObject(*(origin.owner));
}

// �Ҹ���
Component::~Component()
{
	// GameObject* �� ����Ű�� �� �����ϸ� �ȵ�
}
