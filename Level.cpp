#include "PCH.h"
#include "Level.h"
#include "GameObject.h"

// ������
Level::Level(const wstring& name) : Entity(name)
{
}

// �Ҹ���
Level::~Level()
{
	// ������ ��ȯ�ǵ� �÷��̾�� ������Ʈ�� �������� �ȵǹǷ�, 
	// �� ������ �°� ������Ʈ�� ���쵵�� ����
}

// �ʱ�ȭ
void Level::Init()
{
	for (auto object : objects)
	{
		assert(object);
		object->Init();
	}
}

// �� �����Ӹ��� ȣ��
void Level::Tick()
{
	for (auto object : objects)
	{
		assert(object);
		object->Tick();
	}
}

// �� �����Ӹ��� ȣ��
void Level::FinalTick()
{
	for (auto object : objects)
	{
		object->FinalTick();
	}
}

// ������
void Level::Render()
{
	for (auto object : objects)
	{
		object->Render();
	}
}

// ���� ������ ������Ʈ ��� �����
void Level::DeleteObjects()
{
	::Delete(objects);
}