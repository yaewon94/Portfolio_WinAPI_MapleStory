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
	AddObject(Player(L"Player", Vec2(100, 600), Vec2(220, 220)));
	AddObject(Ground(Vec2(0, 800), Vec2(1000, 100)));
	AddObject(Monster(L"Boss_Will", Vec2(400, 700), Vec2(100, 100)));
}

// 레벨 종료시 호출
void Level_Test::Exit()
{
	// 다음 레벨에 안쓸 오브젝트 제거
}