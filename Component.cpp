#include "PCH.h"
#include "Component.h"
#include "GameObject.h"

// ������
Component::Component() : owner(nullptr)
{
}

Component::Component(GameObject& owner) : owner(&owner)
{
}

// ���� ������
Component::Component(const Component& origin) : Entity(origin), owner(nullptr)
{
	// ERROR : �� �ٽ� ���ӿ�����Ʈ�� ��������ڸ� ȣ���ϰ� �Ǽ� ���ѹݺ���
	//owner = origin.owner->Clone();
}

// �Ҹ���
Component::~Component()
{
	// GameObject* �� ����Ű�� ���� Level���� �����Ұ���
	owner = nullptr;
}