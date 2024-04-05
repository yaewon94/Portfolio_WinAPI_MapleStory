#include "PCH.h"
#include "Monster.h"

// ������
Monster::Monster(const wstring& name, Vec2 pos, Vec2 scale) : GameObject(name, pos, scale, LAYER_TYPE::ENEMY)
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