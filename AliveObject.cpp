#include "PCH.h"
#include "AliveObject.h"
#include "TimeManager.h"
#include "Rigidbody.h"

// 생성자
AliveObject::AliveObject(const wstring& name, Vec2 pos, Vec2 scale, LAYER_TYPE layer, float speed, float jumpPower)
	: GameObject(name, pos, scale, layer), speed(speed), jumpPower(jumpPower)
{
}

// 복사 생성자
AliveObject::AliveObject(const AliveObject& origin) : GameObject(origin), speed(origin.speed), jumpPower(origin.jumpPower)
{
}

// 소멸자
AliveObject::~AliveObject()
{
}

// 이동
void AliveObject::Move()
{
	pos += (dir * speed * TimeManager::GetInstance().GetDeltaTime());
}

// 점프
void AliveObject::Jump()
{
	if (!canJump) return;

	Rigidbody* rb = GetComponent<Rigidbody>();
	rb->UseGravity(true);
	rb->AddForce(Vec2::Up() * jumpPower);
}

// 충돌 시작
void AliveObject::OnCollisionEnter(GameObject& other)
{
	if (other.GetLayer() == LAYER_TYPE::GROUND)
	{
		GetComponent<Rigidbody>()->UseGravity(false);
		canJump = true;
	}
}

// 충돌 중
void AliveObject::OnCollisionStay(GameObject& other)
{
}

// 충돌 종료
void AliveObject::OnCollisionExit(GameObject& other)
{
	if (other.GetLayer() == LAYER_TYPE::GROUND)
	{
		GetComponent<Rigidbody>()->UseGravity(true);
		canJump = false;
	}
}