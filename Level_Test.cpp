#include "PCH.h"
#include "Level_Test.h"
#include "GameObject.h"
#include "Player.h"
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
	GameObject* player = AddObject(LAYER_TYPE::PLAYER, Player(L"Player", Vec2(100, 700), Vec2(100, 100)));
	// 컴포넌트 추가
	player->AddComponent<Rigidbody>();
}

// 레벨 종료시 호출
void Level_Test::Exit()
{
	// 다음 레벨에 안쓸 오브젝트 제거
}