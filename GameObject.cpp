#include "PCH.h"
#include "GameObject.h"
#include "Engine.h"
#include "LevelManager.h"
#include "Camera.h"
#include "Component.h"

// static ��� �ʱ�ȭ
Camera* GameObject::mainCamera = nullptr;

// ������
GameObject::GameObject(const wstring& name, Vec2 offset, Vec2 scale, LAYER_TYPE layer, bool isActive)
	: name(name), offset(offset), scale(scale), layer(layer), isActive(isActive)
	, parent(nullptr)
{
}

// ���� ������
GameObject::GameObject(const GameObject& origin)
	: Entity(origin)
	, name(origin.name), offset(origin.offset), scale(origin.scale), layer(origin.layer), isActive(origin.isActive)
	, parent(origin.parent)
{
	// ������ ������ �ִ� �ڽ� ������Ʈ ����
	for (auto& layer : origin.children)
	{
		for (auto child : layer)
		{
			AddChild(*child->Clone());
		}
	}

	// ������ ������ �ִ� ������Ʈ ����
	for (auto component : origin.components)
	{
		components.push_back(component->Clone());
	}

	// ī�޶� ���� x (Level �Ҹ��ڿ��� ���ŵ�)
}

// �Ҹ���
GameObject::~GameObject()
{
	parent = nullptr;

	// �ڽ� ������Ʈ ����
	DeleteChildren();
	
	// ������Ʈ ����
	for (auto component : components)
	{
		if (component != nullptr)
		{
			component->Destroy();
			component = nullptr;
		}
	}
}

// �θ� ������Ʈ ����
void GameObject::SetParent(GameObject& parent)
{
	// ���� ������ ��ϵ� ������Ʈ���� Ȯ��
	if (LevelManager::GetInstance().FindObject(parent) == nullptr)
	{
		Log(LOG_TYPE::LOG_ERROR, L"���� ������ �����ϴ� ������Ʈ�� �ƴմϴ�");
		return;
	}

	// �θ� - �ڽ� ����
	this->parent = &parent;
	parent.AddChild(*this);
}

// �ڽ� ������Ʈ �߰�
GameObject* GameObject::AddChild(GameObject& child)
{
	children[(size_t)child.GetLayer()].push_back(&child);
	child.parent = this;

	// ���� ������ ������Ʈ ��Ͽ� ���
	if (LevelManager::GetInstance().FindObject(child) == nullptr)
	{
		LevelManager::GetInstance().AddObject(child);
	}

	return &child;
}

GameObject* GameObject::AddChild(GameObject&& child)
{
	auto clone = child.Clone();
	children[(size_t)clone->GetLayer()].push_back(clone);
	clone->parent = this;

	// ���� ������ ������Ʈ ��Ͽ� ���
	LevelManager::GetInstance().AddObject(*clone);

	return clone;
}

// �ʱ�ȭ
void GameObject::Init()
{
	for (auto component : components)
	{
		component->Init();
	}
}

// �� �����Ӹ��� ȣ��
void GameObject::FinalTick()
{
	for (auto component : components)
	{
		component->FinalTick();
	}
}

// ������ (�� �����Ӹ��� ȣ��)
void GameObject::Render()
{
	Vec2 realPos = GetPos();
	Engine::GetInstance().Render(mainCamera->GetRenderPos(realPos), scale);
}

// �ڽ� ������Ʈ ����
void GameObject::DeleteChildren()
{
	for (auto& layer : children)
	{
		for (auto child : layer)
		{
			// ���� ������ ��ϵ� ������Ʈ ��Ͽ��� ����
			LevelManager::GetInstance().DeleteObject(*child);

			// ���� ��ü ����
			delete child;
			child = nullptr;
		}
	}
}