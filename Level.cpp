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

// ������Ʈ �߰�
void Level::AddObject(GameObject& object, LAYER_TYPE layer)
{
	assert(&object);
	assert((UINT)layer < objects.size());
	objects[(UINT)layer].push_back(&object);
}

// ������Ʈ ã��
GameObject& Level::FindObject(LAYER_TYPE layer)
{
	assert((UINT)layer < objects.size());
	return *(objects[(UINT)layer][0]);
}

// �ʱ�ȭ
void Level::Init()
{
	for (const auto& layer : objects)
	{
		for (const auto& object : layer)
		{
			assert(object);
			object->Init();
		}
	}
}

// �� �����Ӹ��� ȣ��
void Level::Tick()
{
	for (const auto& layer : objects)
	{
		for (const auto& object : layer)
		{
			assert(object);
			object->Tick();
		}
	}
}

// �� �����Ӹ��� ȣ��
void Level::FinalTick()
{
	for (const auto& layer : objects)
	{
		for (const auto& object : layer)
		{
			object->FinalTick();
		}
	}
}

// ������
void Level::Render()
{
	for (const auto& layer : objects)
	{
		for (const auto& object : layer)
		{
			object->Render();
		}
	}
}

// ���� ������ ������Ʈ ��� �����
void Level::DeleteObjects()
{
	for (auto& layer : objects)
	{
		for (auto& object : layer)
		{
			if (object != nullptr)
			{
				delete object;
				object = nullptr;
			}
		}

		layer.clear();
	}
}