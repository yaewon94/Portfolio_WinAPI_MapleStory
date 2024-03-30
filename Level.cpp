#include "PCH.h"
#include "Level.h"
#include "GameObject.h"

// ������
Level::Level(const wstring& name) : name(name)
{
}

// �Ҹ���
Level::~Level()
{
	// ������ ��ȯ�ǵ� �÷��̾�� ������Ʈ�� �������� �ȵǹǷ�, 
	// �� ������ �°� ������Ʈ�� ���쵵�� ����
}

// ���� ������ ���ӿ�����Ʈ �߰�
GameObject& Level::AddObject(LAYER_TYPE layer, const wstring& name, Vec2 pos, Vec2 scale)
{
	size_t layer_idx = (size_t)layer;
	GameObject* obj = nullptr;

	assert(layer_idx < objects.max_size());
	obj = &GameObject::Create(name, pos, scale);
	objects[layer_idx].push_back(obj);

	return *obj;
}

// �ʱ�ȭ
void Level::Init()
{
	for (auto& layer : objects)
	{
		for (auto object : layer)
		{
			assert(object);
			object->Init();
		}
	}
}

// �� �����Ӹ��� ȣ��
void Level::Tick()
{
	for (auto& layer : objects)
	{
		for (auto object : layer)
		{
			object->Tick();
		}
	}
}

// �� �����Ӹ��� ȣ��
void Level::FinalTick()
{
	for (auto& layer : objects)
	{
		for (auto object : layer)
		{
			object->FinalTick();
		}
	}
}

// �� �����Ӹ��� ������
void Level::Render()
{
	for (auto& layer : objects)
	{
		for (auto object : layer)
		{
			assert(object);
			object->Render();
		}
	}
}

// ���ӿ�����Ʈ ã��
GameObject* Level::FindObject(LAYER_TYPE layer)
{
	size_t layerIdx = (size_t)layer;

	assert(layerIdx < objects.size());

	if (objects[layerIdx][0] == nullptr) return nullptr;
	return objects[layerIdx][0];
}

// ���� ������ ������Ʈ ��� �����
void Level::DeleteObjects()
{
	for (auto& layer : objects)
	{
		for (auto object : layer)
		{
			if (object != nullptr)
			{
				object->Destroy();
				object = nullptr;
			}
		}
	}
}