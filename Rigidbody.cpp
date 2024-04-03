#include "PCH.h"
#include "Rigidbody.h"
#include "TimeManager.h"
#include "GameObject.h"

// ������
Rigidbody::Rigidbody(GameObject& owner, int mass) : Component(owner), mass(mass)
{
}

// ���� ������
Rigidbody::Rigidbody(const Rigidbody& origin) : Component(origin), mass(origin.mass)
{
}

// �̵� ������
Rigidbody::Rigidbody(Rigidbody&& origin) noexcept : Component(std::move(origin))
{
	*this = std::move(origin);
}

// �Ҹ���
Rigidbody::~Rigidbody()
{
}

// ���� ������
Rigidbody& Rigidbody::operator=(const Rigidbody& origin)
{
	mass = origin.mass;
	return *this;
}

// �̵����� ������
Rigidbody& Rigidbody::operator=(Rigidbody&& origin) noexcept
{
	if (this != &origin)
	{
		mass = origin.mass;
		origin.mass = 0;
	}

	return *this;
}

// ������ٵ� �� �߰�
void Rigidbody::AddForce(Vec2 force)
{
	this->force += force;
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
	Vec2 finalVelocity = force + velocity;
	pos += finalVelocity * DT;
	GetOwner()->SetPos(pos);
}