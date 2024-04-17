#include "PCH.h"
#include "AliveObject.h"
#include "FSM.h"
#include "TimeManager.h"
#include "Rigidbody.h"
#include "Skill.h"
#include "SkillObject.h"
#include "Texture.h"

// 생성자
AliveObject::AliveObject(const wstring& name, LAYER_TYPE layer, int MaxHP, int power, float speed, float jumpPower) 
	: GameObject(name, DEFAULT_OBJECT_POS, DEFAULT_OBJECT_SCALE, layer)
	, MaxHP(MaxHP), power(power), speed(speed), jumpPower(jumpPower)
	, skillObject(nullptr)
{
}

// 복사 생성자
AliveObject::AliveObject(const AliveObject& origin) 
	: GameObject(origin)
	, MaxHP(origin.MaxHP), power(origin.power), speed(origin.speed), jumpPower(origin.jumpPower)
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
	if (canMove)
	{
		if (canJump) GetComponent<FSM>()->ChangeState(OBJECT_STATE::WALK);
		offset += dir * speed * TimeManager::GetInstance().GetDeltaTime();
		prevDir = dir;
	}
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
	if (other.GetLayer() == LAYER_TYPE::WALL)
	{
		canMove = false;
	}
}

// 충돌 중
void AliveObject::OnCollisionStay(GameObject& other)
{
	if (other.GetLayer() == LAYER_TYPE::WALL)
	{
		if (prevDir != dir)
		{
			canMove = true;
		}
	}
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

// 체력 변화시 호출
void AliveObject::OnChangeHP(int changedHP)
{
	// 현재체력 변경
	curHP += changedHP;
	if (curHP < 0) curHP = 0;
	else if (curHP > MaxHP) curHP = MaxHP;

	// 자신의 체력바 UI에 반영
	HP_fillTex->SetRenderRatio((float)curHP/MaxHP, 1.f);
}