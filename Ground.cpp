#include "PCH.h"
#include "Ground.h"
#include "Collider.h"

// ������
Ground::Ground(Vec2 pos, Vec2 scale) : GameObject(L"", pos, scale, LAYER_TYPE::GROUND)
{
}

// ���� ������
Ground::Ground(const Ground& origin) : GameObject(origin)
{
}

// �Ҹ���
Ground::~Ground()
{
}

// �ʱ�ȭ
void Ground::Init()
{
	// ������Ʈ �߰�
	AddComponent<Collider>()->SetScale(Vec2(scale.x, 10));
}

void Ground::OnCollisionEnter(GameObject& other)
{
}

void Ground::OnCollisionStay(GameObject& other)
{
}

void Ground::OnCollisionExit(GameObject& other)
{
}
