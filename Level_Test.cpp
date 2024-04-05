#include "PCH.h"
#include "Level_Test.h"
#include "GameObject.h"
#include "Ground.h"
#include "Monster.h"
#include "Player.h"
#include "Collider.h"
#include "Rigidbody.h"

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
	GameObject* player = AddObject(Player(L"Player", Vec2(100, 700), Vec2(100, 100)));
	player->AddComponent<Rigidbody>();
	player->AddComponent<Collider>();
	GameObject* ground = AddObject(Ground(Vec2(0, 800), Vec2(1000, 100)));
	ground->AddComponent<Collider>()->SetScale(Vec2(ground->GetScale().x, 10));
	GameObject* monster = AddObject(Monster(L"Boss_Will", Vec2(400, 700), Vec2(100, 100)));
	monster->AddComponent<Collider>();
}

// 레벨 종료시 호출
void Level_Test::Exit()
{
	// 다음 레벨에 안쓸 오브젝트 제거
}