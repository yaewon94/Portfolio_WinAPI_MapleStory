#include "PCH.h"
#include "AliveObject.h"
#include "FSM.h"
#include "TimeManager.h"
#include "Rigidbody.h"
#include "Skill.h"
#include "SkillObject.h"

// 생성자
AliveObject::AliveObject(const wstring& name, Vec2<float> offset, Vec2<int> scale, LAYER_TYPE layer, float speed, float jumpPower)
	: GameObject(name, offset, scale, layer), speed(speed), jumpPower(jumpPower)
	, skillObject(nullptr)
{
}

// 복사 생성자
AliveObject::AliveObject(const AliveObject& origin) 
	: GameObject(origin), speed(origin.speed), jumpPower(origin.jumpPower)
	, skillObject(nullptr)
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

	// SkillObject*는 레벨에서 부모 게임오브젝트 삭제될 때 삭제됨. 지우지 말것
}

// 이동
void AliveObject::Move()
{
	offset += dir * speed * TimeManager::GetInstance().GetDeltaTime();
}

// 점프
void AliveObject::Jump()
{
	if (!canJump) return;

	GetComponent<FSM>()->ChangeState(OBJECT_STATE::JUMP);
	Rigidbody* rb = GetComponent<Rigidbody>();
	rb->UseGravity(true);
	rb->AddForce(Vec2<float>::Up() * jumpPower);
}

// 충돌 시작
void AliveObject::OnCollisionEnter(GameObject& other)
{
	if (other.GetLayer() == LAYER_TYPE::GROUND)
	{
		if (!canJump)
		{
			GetComponent<FSM>()->ChangeState(OBJECT_STATE::IDLE);
			GetComponent<Rigidbody>()->UseGravity(false);
			canJump = true;
		}
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