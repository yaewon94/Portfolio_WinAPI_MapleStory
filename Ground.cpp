#include "PCH.h"
#include "Ground.h"

// ������
Ground::Ground(Vec2 pos, Vec2 scale) : GameObject(L"", pos, scale, LAYER_TYPE::GROUND)
{
}

// ���� ������
Ground::Ground(const Ground& origin) : GameObject(origin)
{
}

// �Ҹ���
Ground::~Ground()
{
}

void Ground::OnCollisionEnter(GameObject& other)
{
}

void Ground::OnCollisionStay(GameObject& other)
{
}

void Ground::OnCollisionExit(GameObject& other)
{
}
