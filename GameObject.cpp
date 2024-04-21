#include "PCH.h"
#include "GameObject.h"
#include "Animator.h"
#include "Engine.h"
#include "LevelManager.h"
#include "Camera.h"
#include "Component.h"
#include "Texture.h"

// ������
GameObject::GameObject(LAYER_TYPE layer) : layer(layer), isActive(true), texture(nullptr), parent(nullptr)
{
}

GameObject::GameObject(const wstring& name, Vec2<float> offset, Vec2<int> scale, LAYER_TYPE layer, bool isActive)
	: name(name), offset(offset), scale(scale), layer(layer),isActive(isActive)
	, texture(nullptr), parent(nullptr)
{
}

// ���� ������
GameObject::GameObject(const GameObject& origin)
	: Entity(origin)
	, name(origin.name), offset(origin.offset), scale(origin.scale)
	, layer(origin.layer), isActive(origin.isActive), texture(origin.texture)
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
		Component* clone = component->Clone();
		clone->SetOwner(*this);
		components.push_back(clone);
		// ERROR : ������Ʈ ���� ����
		//components.push_back(component->Clone());
	}
}

// �Ҹ���
GameObject::~GameObject()
{

	// Texture ��ü ���Ŵ� AssetManager ���
	texture = nullptr;

	// �θ� ������Ʈ�� ����� �ȉ�
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

// ������ ��ǥ ��������
Vec2<float> GameObject::GetRenderPos()
{
	Vec2 realPos = GetRealPos();
	return Level::GetMainCamera().GetRenderPos(realPos);
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

// �ʵ� �� ����
void GameObject::Set(Vec2<float> offset, Vec2<int> scale)
{
	this->offset = offset;
	this->scale = scale;
}

// ������Ʈ Ȱ��ȭ/��Ȱ��ȭ
void GameObject::SetActive(bool flag)
{
	// ������Ʈ Ȱ��ȭ/��Ȱ��ȭ
	for (auto component : components)
	{
		component->SetActive(flag);
	}

	// �ʵ尪 ����
	isActive = flag;

	// �ڽ� ������Ʈ�� ���������� Ȱ��ȭ/��Ȱ��ȭ
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

	SetActive(isActive);
}

// �� �����Ӹ��� ȣ��
void GameObject::FinalTick()
{
	for (auto component : components)
	{
		if (component->IsActive()) component->FinalTick();
	}
}

// ������ (�� �����Ӹ��� ȣ��)
void GameObject::Render()
{
	Animator* animator = GetComponent<Animator>();
	if (animator != nullptr) animator->Render();
	else if (texture != nullptr)
	{
		texture->Render((int)(GetRenderPos().x - scale.x * 0.5f), (int)(GetRenderPos().y - scale.y * 0.5f), scale.x, scale.y);
	}
}

// �ڽ� ������Ʈ ����
void GameObject::DeleteChildren()
{
	for (auto& layer : children)
	{

		for (auto child : layer)
		{
			// ���� ������ ��ϵ� ������Ʈ ��Ͽ��� ����
			LevelManager::GetInstance().DeleteObjectFromList(*child);

			// ���� ��ü ����
			//delete child;
			child->Destroy();
			child = nullptr;

		}
	}
}