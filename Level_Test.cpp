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
	GameObject* player = AddObject(Player(L"Player", Vec2(100, 700), Vec2(100, 100)));
	player->AddComponent<Rigidbody>();
	player->AddComponent<Collider>();
	GameObject* ground = AddObject(Ground(Vec2(0, 800), Vec2(1000, 100)));
	ground->AddComponent<Collider>()->SetScale(Vec2(ground->GetScale().x, 10));
	GameObject* monster = AddObject(Monster(L"Boss_Will", Vec2(400, 700), Vec2(100, 100)));
	monster->AddComponent<Collider>();
}

// ���� ����� ȣ��
void Level_Test::Exit()
{
	// ���� ������ �Ⱦ� ������Ʈ ����
}