#include "PCH.h"
#include "Level.h"
#include "GameObject.h"
#include "Camera.h"

// ������
Level::Level(const wstring& name) : name(name), mainCamera(new Camera)
{
	GameObject::SetMainCamera(mainCamera);
}

// �Ҹ���
Level::~Level()
{
	// ī�޶� ����
	if (mainCamera != nullptr)
	{
		delete mainCamera;
		mainCamera = nullptr;
	}
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
	// ī�޶�
	mainCamera->FinalTick();

	// ������Ʈ
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