#include "PCH.h"
#include "AliveObject.h"
#include "TimeManager.h"
#include "Rigidbody.h"
#include "Skill.h"

// 생성자
AliveObject::AliveObject(const wstring& name, Vec2 pos, Vec2 scale, LAYER_TYPE layer, float speed, float jumpPower)
	: GameObject(name, pos, scale, layer), speed(speed), jumpPower(jumpPower)
{
}

// 복사 생성자
AliveObject::AliveObject(const AliveObject& origin) 
	: GameObject(origin), speed(origin.speed), jumpPower(origin.jumpPower)
{
	for (Skill* skill : origin.skills)
	{
		if(skill != nullptr) skills.push_back(skill);
	}
}

// 소멸자
AliveObject::~AliveObject()
{
	for (Skill* skill : skills)
	{
		if (skill != nullptr) skill = nullptr;
	}
}

// 사용 가능한 스킬 추가
void AliveObject::AddSkill(Skill& skill)
{
	skills.push_back(&skill);
}

// 이동
void AliveObject::Move()
{
	offset += (dir * speed * TimeManager::GetInstance().GetDeltaTime());
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