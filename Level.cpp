#include "PCH.h"
#include "Level.h"
#include "Camera.h"
#include "Map.h"

// static ��� �ʱ�ȭ
Camera* Level::mainCamera = new Camera;

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

// �ʱ�ȭ
void Level::Init()
{
	// ī�޶�
	mainCamera->Init();

	// ������Ʈ
	for (auto& layer : objects)
	{
		for (auto object : layer)
		{
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
			if (object->IsActive()) object->Tick();
		}
	}
}

// �� �����Ӹ��� ȣ��
void Level::FinalTick()
{
	// ī�޶�
	mainCamera->FinalTick();

	// ������Ʈ
	for (auto& layer : objects)
	{
		for (auto object : layer)
		{
			if (object->IsActive()) object->FinalTick();
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
			if (object->IsActive()) object->Render();
		}
	}
}

// ���ӿ�����Ʈ ã��
GameObject* Level::FindObject(LAYER_TYPE layer)
{
	GameObject* obj = objects[(size_t)layer][0];
	return obj;
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