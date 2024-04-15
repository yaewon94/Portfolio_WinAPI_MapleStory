#include "PCH.h"
#include "Ground.h"
#include "Collider.h"

// ������
Ground::Ground(Vec2<float> pos, Vec2<int> scale) : GameObject(L"", pos, scale, LAYER_TYPE::GROUND)
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
	Collider* collider = AddComponent<Collider>();
	//collider->SetScale(Vec2(scale.x, 10));
	//collider->SetOffset(Vec2(offset.x, (collider->GetScale().y - scale.y) * 0.5f));

	// �θ� Init() ȣ��
	GameObject::Init();
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
