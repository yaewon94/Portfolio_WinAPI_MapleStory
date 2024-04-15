#include "PCH.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "Camera.h"
#include "DebugRender.h"
#include "Level.h"

// 생성자
Collider::Collider(GameObject& owner) : Component(owner), offset(Vec2(0, 0)), scale(owner.GetScale())
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

// 렌더링 좌표 반환
Vec2 Collider::GetRenderPos()
{
	Vec2 realPos = GetPos();
	return Level::GetMainCamera().GetRenderPos(realPos);
}

// 초기화
void Collider::Init()
{
	// 디버그 렌더링 등록
	DebugRender::GetInstance().AddCollider(this);
}