#include "PCH.h"
#include "Level_Test.h"
#include "GameObject.h"
#include "Player.h"
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
	GameObject* player = AddObject(LAYER_TYPE::PLAYER, Player(L"Player", Vec2(100, 700), Vec2(100, 100)));
	// ������Ʈ �߰�
	player->AddComponent<Rigidbody>();
}

// ���� ����� ȣ��
void Level_Test::Exit()
{
	// ���� ������ �Ⱦ� ������Ʈ ����
}