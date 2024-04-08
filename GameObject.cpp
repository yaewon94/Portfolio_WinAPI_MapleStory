#include "PCH.h"
#include "GameObject.h"
#include "Engine.h"
#include "LevelManager.h"
#include "Camera.h"
#include "Component.h"

// static ��� �ʱ�ȭ
Camera* GameObject::mainCamera = nullptr;

// ������
GameObject::GameObject(const wstring& name, Vec2 offset, Vec2 scale, LAYER_TYPE layer)
	: name(name), offset(offset), scale(scale), layer(layer), parent(nullptr)
{
}

// ���� ������
GameObject::GameObject(const GameObject& origin)
	: Entity(origin)
	, name(origin.name), offset(origin.offset), scale(origin.scale), layer(origin.layer), parent(origin.parent)
{
	// ������ ������ �ִ� �ڽ� ������Ʈ ����
	for (auto child : origin.children)
	{
		children.push_back(child->Clone());
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
void GameObject::AddChild(GameObject& child)
{
	children.push_back(&child);
	child.parent = this;

	// ���� ������ ������Ʈ ��Ͽ� ���
	if (LevelManager::GetInstance().FindObject(child) == nullptr)
	{
		LevelManager::GetInstance().AddObject(child);
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
	Engine::GetInstance().Render(mainCamera->GetRenderPos(this->offset), this->scale);
}

// �ڽ� ������Ʈ ����
void GameObject::DeleteChildren()
{
	for (auto child : children)
	{
		if (child != nullptr)
		{
			// ���� ������ ��ϵ� ������Ʈ ��Ͽ��� ����
			LevelManager::GetInstance().DeleteObject(*child);

			// ���� ��ü ����
			delete child;
			child = nullptr;
		}
	}
}