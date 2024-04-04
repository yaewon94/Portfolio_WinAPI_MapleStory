#include "PCH.h"
#include "Level_Test.h"
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "Rigidbody.h"
#include "Collider.h"

// 생성자
Level_Test::Level_Test() : Level(L"Level_Test")
{
}

// 소멸자
Level_Test::~Level_Test()
{
}

// 레벨 진입시 호출
void Level_Test::Enter()
{
	// 오브젝트 추가
	GameObject* player = AddObject(LAYER_TYPE::PLAYER, Player(L"Player", Vec2(100, 700), Vec2(100, 100)));
	player->AddComponent<Rigidbody>();
	player->AddComponent<Collider>()->Set(Vec2(0,0), player->GetScale());
	GameObject* ground = AddObject(LAYER_TYPE::GROUND, Ground(Vec2(0,800), Vec2(1000, 100)));
	ground->AddComponent<Collider>()->Set(Vec2(0,0), Vec2(ground->GetScale().x, 10));
}

// 레벨 종료시 호출
void Level_Test::Exit()
{
	// 다음 레벨에 안쓸 오브젝트 제거
}