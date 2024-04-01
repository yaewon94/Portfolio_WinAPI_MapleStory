#include "PCH.h"
#include "Level_Test.h"
#include "GameObject.h"
#include "Player.h"

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
	GameObject& player = AddObject(LAYER_TYPE::PLAYER, L"Player", Vec2(100, 100), Vec2(100, 100));
	// ������Ʈ �߰�
	player.AddComponent(Player(player));
}

// ���� ����� ȣ��
void Level_Test::Exit()
{
	// ���� ������ �Ⱦ� ������Ʈ ����
}