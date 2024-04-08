#include "PCH.h"
#include "AliveObject.h"
#include "TimeManager.h"
#include "Rigidbody.h"

// ������
AliveObject::AliveObject(const wstring& name, Vec2 pos, Vec2 scale, LAYER_TYPE layer, float speed, float jumpPower)
	: GameObject(name, pos, scale, layer), speed(speed), jumpPower(jumpPower)
{
}

// ���� ������
AliveObject::AliveObject(const AliveObject& origin) : GameObject(origin), speed(origin.speed), jumpPower(origin.jumpPower)
{
}

// �Ҹ���
AliveObject::~AliveObject()
{
}

// �̵�
void AliveObject::Move()
{
	pos += (dir * speed * TimeManager::GetInstance().GetDeltaTime());
}

// ����
void AliveObject::Jump()
{
	if (!canJump) return;

	Rigidbody* rb = GetComponent<Rigidbody>();
	rb->UseGravity(true);
	rb->AddForce(Vec2::Up() * jumpPower);
}

// �浹 ����
void AliveObject::OnCollisionEnter(GameObject& other)
{
	if (other.GetLayer() == LAYER_TYPE::GROUND)
	{
		GetComponent<Rigidbody>()->UseGravity(false);
		canJump = true;
	}
}

// �浹 ��
void AliveObject::OnCollisionStay(GameObject& other)
{
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