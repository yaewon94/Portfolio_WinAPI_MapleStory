#include "PCH.h"
#include "Monster.h"
#include "Collider.h"

// ������
Monster::Monster(const wstring& name, Vec2<float> pos, Vec2<int> scale) 
	: GameObject(name, pos, scale, LAYER_TYPE::ENEMY)
{
}

// ���� ������
Monster::Monster(const Monster& origin) : GameObject(origin)
{
}

// �Ҹ���
Monster::~Monster()
{
}

// �ʱ�ȭ
void Monster::Init()
{
	AddComponent<Collider>();
}

// �浹 ����
void Monster::OnCollisionEnter(GameObject& other)
{
}

// �浹 ��
void Monster::OnCollisionStay(GameObject& other)
{
}

// �浹 ����
void Monster::OnCollisionExit(GameObject& other)
{
}