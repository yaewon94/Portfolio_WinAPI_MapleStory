#include "PCH.h"
#include "Ground.h"
#include "Collider.h"

// 생성자
Ground::Ground(Vec2 pos, Vec2 scale) : GameObject(L"", pos, scale, LAYER_TYPE::GROUND)
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
	AddComponent<Collider>()->SetScale(Vec2(scale.x, 10));
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
