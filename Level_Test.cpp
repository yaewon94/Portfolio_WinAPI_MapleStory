#include "PCH.h"
#include "Level_Test.h"
#include "Player.h"

// ������
Level_Test::Level_Test() : Level(L"�׽�Ʈ ����")
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
	GameObject* player = new Player(L"Player", Vec2(500, 500), Vec2(100, 100));
	objects.push_back(player);
}

// ���� ����� ȣ��
void Level_Test::Exit()
{
	// ���� ������ �Ⱦ� ������Ʈ ����
}