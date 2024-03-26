#include "PCH.h"
#include "Level.h"
#include "GameObject.h"

// 생성자
Level::Level(const wstring& name) : Entity(name)
{
}

// 소멸자
Level::~Level()
{
	// 레벨이 전환되도 플레이어같은 오브젝트는 지워지면 안되므로, 
	// 각 레벨에 맞게 오브젝트를 지우도록 구현
}

// 초기화
void Level::Init()
{
	for (auto object : objects)
	{
		assert(object);
		object->Init();
	}
}

// 매 프레임마다 호출
void Level::Tick()
{
	for (auto object : objects)
	{
		assert(object);
		object->Tick();
	}
}

// 매 프레임마다 호출
void Level::FinalTick()
{
	for (auto object : objects)
	{
		object->FinalTick();
	}
}

// 렌더링
void Level::Render()
{
	for (auto object : objects)
	{
		object->Render();
	}
}

// 현재 레벨의 오브젝트 모두 지우기
void Level::DeleteObjects()
{
	::Delete(objects);
}