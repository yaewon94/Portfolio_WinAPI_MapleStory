#include "PCH.h"
#include "Level_Test.h"
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "Rigidbody.h"
#include "Collider.h"

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
	GameObject* player = AddObject(LAYER_TYPE::PLAYER, Player(L"Player", Vec2(100, 700), Vec2(100, 100)));
	player->AddComponent<Rigidbody>();
	player->AddComponent<Collider>()->Set(Vec2(0,0), player->GetScale());
	GameObject* ground = AddObject(LAYER_TYPE::GROUND, Ground(Vec2(0,800), Vec2(1000, 100)));
	ground->AddComponent<Collider>()->Set(Vec2(0,0), Vec2(ground->GetScale().x, 10));
}

// ���� ����� ȣ��
void Level_Test::Exit()
{
	// ���� ������ �Ⱦ� ������Ʈ ����
}