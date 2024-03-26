#include "PCH.h"
#include "Level_Test.h"
#include "Player.h"

// 생성자
Level_Test::Level_Test() : Level(L"테스트 레벨")
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
	GameObject* player = new Player(L"Player", Vec2(500, 500), Vec2(100, 100));
	objects.push_back(player);
}

// 레벨 종료시 호출
void Level_Test::Exit()
{
	// 다음 레벨에 안쓸 오브젝트 제거
}