#include "PCH.h"
#include "Wall.h"
#include "Collider.h"

// ������
Wall::Wall() : GameObject(LAYER_TYPE::WALL)
{
}

// ���� ������
Wall::Wall(const Wall& origin) : GameObject(origin)
{
}

// �Ҹ���
Wall::~Wall()
{
}

// �ʱ�ȭ
void Wall::Init()
{
	// ������Ʈ �߰�
	Collider* collider = AddComponent<Collider>();

	// �θ� Init() ȣ��
	GameObject::Init();
}

void Wall::OnCollisionEnter(GameObject& other)
{
}

void Wall::OnCollisionStay(GameObject& other)
{
}

void Wall::OnCollisionExit(GameObject& other)
{
}
