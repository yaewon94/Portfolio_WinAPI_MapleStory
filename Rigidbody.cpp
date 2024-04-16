#include "PCH.h"
#include "Rigidbody.h"
#include "TimeManager.h"
#include "GameObject.h"

// 생성자
Rigidbody::Rigidbody(GameObject& owner, float mass) : Component(owner), mass(mass)
{
}

// 복사 생성자
Rigidbody::Rigidbody(const Rigidbody& origin)
	: Component(origin)
	, mass(origin.mass), force(origin.force), velocity(origin.velocity), useGravity(origin.useGravity)
{
}

// 소멸자
Rigidbody::~Rigidbody()
{
}


// 매 프레임마다 호출
void Rigidbody::FinalTick()
{
	if (!useGravity) return;
	
	float DT = TimeManager::GetInstance().GetDeltaTime();
	Vec2 pos = GetOwner()->GetRealPos();

	// 중력 방향으로 가속도 적용
	velocity += Vec2<float>::Down() * mass * 9.8f;

	// 최종 속도 적용
	pos += velocity * DT;
	GetOwner()->SetRealPos(pos);
}