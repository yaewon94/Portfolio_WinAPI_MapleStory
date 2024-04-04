#include "PCH.h"
#include "Collider.h"
#include "CollisionManager.h"

// 생성자
Collider::Collider(GameObject& owner) : Component(owner), offset(owner.GetPos()), scale(owner.GetScale())
{
	// 충돌 처리 등록
	CollisionManager::GetInstance().AddCollider(*this);
}

// 복사 생성자
Collider::Collider(const Collider& origin) : Component(origin), offset(origin.offset), scale(origin.scale)
{
	// 충돌 처리 등록
	CollisionManager::GetInstance().AddCollider(*this);
}

// 소멸자
Collider::~Collider()
{
	// 충돌 처리 삭제
	CollisionManager::GetInstance().RemoveCollider(*this);
}

// 멤버 값 세팅
void Collider::Set(Vec2 offset, Vec2 scale)
{
	this->offset = offset;
	this->scale = scale;
}