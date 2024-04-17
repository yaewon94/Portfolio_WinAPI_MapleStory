#include "PCH.h"
#include "AliveObject.h"
#include "FSM.h"
#include "TimeManager.h"
#include "Rigidbody.h"
#include "Skill.h"
#include "SkillObject.h"
#include "Texture.h"

// ������
AliveObject::AliveObject(const wstring& name, LAYER_TYPE layer, int MaxHP, int power, float speed, float jumpPower) 
	: GameObject(name, DEFAULT_OBJECT_POS, DEFAULT_OBJECT_SCALE, layer)
	, MaxHP(MaxHP), power(power), speed(speed), jumpPower(jumpPower)
	, skillObject(nullptr)
{
}

// ���� ������
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

// �Ҹ���
AliveObject::~AliveObject()
{
	for (Skill* skill : skills)
	{
		if (skill != nullptr) skill = nullptr;
	}

	// SkillObject*�� �������� �θ� ���ӿ�����Ʈ ������ �� ������. ������ ����
}

// �̵�
void AliveObject::Move()
{
	if (canMove)
	{
		if (canJump) GetComponent<FSM>()->ChangeState(OBJECT_STATE::WALK);
		offset += dir * speed * TimeManager::GetInstance().GetDeltaTime();
		prevDir = dir;
	}
}

// ����
void AliveObject::Jump()
{
	if (!canJump) return;

	GetComponent<FSM>()->ChangeState(OBJECT_STATE::JUMP);
	Rigidbody* rb = GetComponent<Rigidbody>();
	rb->UseGravity(true);
	rb->AddForce(Vec2<float>::Up() * jumpPower);
}

// �浹 ����
void AliveObject::OnCollisionEnter(GameObject& other)
{
	if (other.GetLayer() == LAYER_TYPE::WALL)
	{
		canMove = false;
	}
}

// �浹 ��
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

// �浹 ����
void AliveObject::OnCollisionExit(GameObject& other)
{
	if (other.GetLayer() == LAYER_TYPE::GROUND)
	{
		GetComponent<Rigidbody>()->UseGravity(true);
		canJump = false;
	}
}

// ü�� ��ȭ�� ȣ��
void AliveObject::OnChangeHP(int changedHP)
{
	// ����ü�� ����
	curHP += changedHP;
	if (curHP < 0) curHP = 0;
	else if (curHP > MaxHP) curHP = MaxHP;

	// �ڽ��� ü�¹� UI�� �ݿ�
	HP_fillTex->SetRenderRatio((float)curHP/MaxHP, 1.f);
}