#include "PCH.h"
#include "Collider.h"
#include "CollisionManager.h"

// 积己磊
Collider::Collider(GameObject& owner) : Component(owner), offset(Vec2(0,0)), scale(owner.GetScale())
{
	// 面倒 贸府 殿废
	CollisionManager::GetInstance().AddCollider(*this);
}

// 汗荤 积己磊
Collider::Collider(const Collider& origin) : Component(origin), offset(origin.offset), scale(origin.scale)
{
	// 面倒 贸府 殿废
	CollisionManager::GetInstance().AddCollider(*this);
}

// 家戈磊
Collider::~Collider()
{
	// 面倒 贸府 昏力
	CollisionManager::GetInstance().RemoveCollider(*this);
}