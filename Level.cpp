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
	
	if (objectMap.find(layer) == objectMap.end())
	{
		vector<GameObject*> objects;
		objects.push_back(&object);
		objectMap.insert(make_pair(layer, objects));
	}
	else
	{
		vector<GameObject*>& objects = objectMap.find(layer)->second;
		objects.push_back(&object);
	}
}

// ������Ʈ ã��
GameObject& Level::FindObject(LAYER_TYPE layer)
{
	if (objectMap.find(layer) == objectMap.end()) throw GameException(LAYER_NAME[(UINT)layer] + L" ������Ʈ�� ã�� �� �����ϴ�");
	return *(objectMap.find(layer)->second[0]);
}

// �ʱ�ȭ
void Level::Init()
{
	for (const auto& objects : objectMap)
	{
		for (const auto object : objects.second)
		{
			assert(object);
			object->Init();
		}
	}
}

// �� �����Ӹ��� ȣ��
void Level::Tick()
{
	for (const auto& objects : objectMap)
	{
		for (const auto& object : objects.second)
		{
			assert(object);
			object->Tick();
		}
	}
}

// �� �����Ӹ��� ȣ��
void Level::FinalTick()
{
	for (const auto& objects : objectMap)
	{
		for (const auto object : objects.second)
		{
			object->FinalTick();
		}
	}
}

// ������
void Level::Render()
{
	for (const auto& objects : objectMap)
	{
		for (const auto object : objects.second)
		{
			object->Render();
		}
	}
}

// ���� ������ ������Ʈ ��� �����
void Level::DeleteObjects()
{
	for (auto& objects : objectMap)
	{
		for (auto object : objects.second)
		{
			if (object != nullptr)
			{
				delete object;
				object = nullptr;
			}
		}

		objects.second.clear();
	}

	objectMap.clear();
}