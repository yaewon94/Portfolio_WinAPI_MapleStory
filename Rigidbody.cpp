#include "PCH.h"
#include "Rigidbody.h"
#include "TimeManager.h"
#include "GameObject.h"

// ������
Rigidbody::Rigidbody(GameObject& owner, float mass) : Component(owner), mass(mass)
{
}

// ���� ������
Rigidbody::Rigidbody(const Rigidbody& origin)
	: Component(origin), mass(origin.mass), force(origin.force), velocity(origin.velocity), useGravity(origin.useGravity)
{
}

// �Ҹ���
Rigidbody::~Rigidbody()
{
}


// �� �����Ӹ��� ȣ��
void Rigidbody::FinalTick()
{
	if (!useGravity) return;

	float DT = TimeManager::GetInstance().GetDeltaTime();
	Vec2 pos = GetOwner()->GetPos();

	// �߷� �������� ���ӵ� ����
	velocity += Vec2::Down() * mass * 9.8f;

	// ���� �ӵ� ����
	pos += velocity * DT;
	GetOwner()->SetPos(pos);
}