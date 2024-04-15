#include "PCH.h"
#include "Wall.h"
#include "Collider.h"

// 생성자
Wall::Wall(Vec2<float> pos, Vec2<int> scale) : GameObject(L"", pos, scale, LAYER_TYPE::WALL)
{
}

// 복사 생성자
Wall::Wall(const Wall& origin) : GameObject(origin)
{
}

// 소멸자
Wall::~Wall()
{
}

// 초기화
void Wall::Init()
{
	// 컴포넌트 추가
	Collider* collider = AddComponent<Collider>();

	// 부모 Init() 호출
	GameObject::Init();
}

void Wall::OnCollisionEnter(GameObject& other)
{
}

void Wall::OnCollisionStay(GameObject& other)
{
}

void Wall::OnCollisionExit(GameObject& other)
{
}
