#include "PCH.h"
#include "Rigidbody.h"
#include "TimeManager.h"
#include "GameObject.h"

// 생성자
Rigidbody::Rigidbody(GameObject& owner, int mass) : Component(owner), mass(mass)
{
}

// 복사 생성자
Rigidbody::Rigidbody(const Rigidbody& origin) : Component(origin), mass(origin.mass)
{
}

// 이동 생성자
Rigidbody::Rigidbody(Rigidbody&& origin) noexcept : Component(std::move(origin))
{
	*this = std::move(origin);
}

// 소멸자
Rigidbody::~Rigidbody()
{
}

// 대입 연산자
Rigidbody& Rigidbody::operator=(const Rigidbody& origin)
{
	mass = origin.mass;
	return *this;
}

// 이동대입 연산자
Rigidbody& Rigidbody::operator=(Rigidbody&& origin) noexcept
{
	if (this != &origin)
	{
		mass = origin.mass;
		origin.mass = 0;
	}

	return *this;
}

// 리지드바디에 힘 추가
void Rigidbody::AddForce(Vec2 force)
{
	this->force += force;
}

// 매 프레임마다 호출
void Rigidbody::FinalTick()
{
	if (!useGravity) return;

	float DT = TimeManager::GetInstance().GetDeltaTime();
	Vec2 pos = GetOwner()->GetPos();

	// 중력 방향으로 가속도 적용
	velocity += Vec2::Down() * mass * 9.8f;

	// 최종 속도 적용
	Vec2 finalVelocity = force + velocity;
	pos += finalVelocity * DT;
	GetOwner()->SetPos(pos);
}