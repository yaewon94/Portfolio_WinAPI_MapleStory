#include "PCH.h"
#include "Ground.h"
#include "Collider.h"

// 생성자
Ground::Ground(Vec2<float> pos, Vec2<int> scale) : GameObject(L"", pos, scale, LAYER_TYPE::GROUND)
{
}

// 복사 생성자
Ground::Ground(const Ground& origin) : GameObject(origin)
{
}

// 소멸자
Ground::~Ground()
{
}

// 초기화
void Ground::Init()
{
	// 컴포넌트 추가
	Collider* collider = AddComponent<Collider>();
	//collider->SetScale(Vec2(scale.x, 10));
	//collider->SetOffset(Vec2(offset.x, (collider->GetScale().y - scale.y) * 0.5f));

	// 부모 Init() 호출
	GameObject::Init();
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
