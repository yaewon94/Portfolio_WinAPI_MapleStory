#include "PCH.h"
#include "Monster.h"

// 생성자
Monster::Monster(const wstring& name, Vec2 pos, Vec2 scale) : GameObject(name, pos, scale, LAYER_TYPE::ENEMY)
{
}

// 복사 생성자
Monster::Monster(const Monster& origin) : GameObject(origin)
{
}

// 소멸자
Monster::~Monster()
{
}

// 충돌 진입
void Monster::OnCollisionEnter(GameObject& other)
{
}

// 충돌 중
void Monster::OnCollisionStay(GameObject& other)
{
}

// 충돌 종료
void Monster::OnCollisionExit(GameObject& other)
{
}