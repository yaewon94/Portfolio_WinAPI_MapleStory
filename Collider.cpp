#include "PCH.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "Camera.h"
#include "DebugRender.h"
#include "Level.h"

// ������
Collider::Collider(GameObject& owner) : Component(owner), offset(Vec2(0,0)), scale(owner.GetScale())
{
	// �浹 ó�� ���
	CollisionManager::GetInstance().AddCollider(*this);
}

// ���� ������
Collider::Collider(const Collider& origin) : Component(origin), offset(origin.offset), scale(origin.scale)
{
	// �浹 ó�� ���
	CollisionManager::GetInstance().AddCollider(*this);
}

// �Ҹ���
Collider::~Collider()
{
	// �浹 ó�� ����
	CollisionManager::GetInstance().RemoveCollider(*this);
}

// ������ ��ǥ ��ȯ
Vec2 Collider::GetRenderPos()
{
	Vec2 realPos = GetPos();
	return Level::GetMainCamera().GetRenderPos(realPos);
}

// �ʱ�ȭ
void Collider::Init()
{
	// ����� ������ ���
	DebugRender::GetInstance().AddCollider(this);
}