#include "PCH.h"
#include "Level_Test.h"
#include "GameObject.h"
#include "Ground.h"
#include "Monster.h"
#include "Player.h"
#include "Collider.h"
#include "Rigidbody.h"

// ������
Level_Test::Level_Test() : Level(L"Level_Test")
{
}

// �Ҹ���
Level_Test::~Level_Test()
{
}

// ���� ���Խ� ȣ��
void Level_Test::Enter()
{
	// ������Ʈ �߰�
	AddObject(Player(L"Player", Vec2(100, 600), Vec2(220, 220)));
	AddObject(Ground(Vec2(0, 800), Vec2(1000, 100)));
	AddObject(Monster(L"Boss_Will", Vec2(400, 700), Vec2(100, 100)));
}

// ���� ����� ȣ��
void Level_Test::Exit()
{
	// ���� ������ �Ⱦ� ������Ʈ ����
}