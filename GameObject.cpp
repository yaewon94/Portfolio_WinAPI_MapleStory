#include "PCH.h"
#include "GameObject.h"
#include "Engine.h"
#include "Component.h"

// ������
GameObject::GameObject(const wstring& name, Vec2 pos, Vec2 scale)
	: name(name), pos(pos), scale(scale)
{
}

// ���� ������
GameObject::GameObject(const GameObject& origin) : Entity(origin)
, name(origin.name), pos(origin.pos), scale(origin.scale)
{
	*this = origin;
}

// �̵� ������
GameObject::GameObject(GameObject&& origin) noexcept : Entity(std::move(origin))
{
	*this = std::move(origin);
}

// �Ҹ���
GameObject::~GameObject()
{
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

// ���� ������
GameObject& GameObject::operator=(const GameObject& origin)
{
	name = origin.name;
	pos = origin.pos;
	scale = origin.scale;
	
	// ���� ������Ʈ clear
	for (auto component : components)
	{
		if (component != nullptr)
		{
			component->Destroy();
			component = nullptr;
		}
	}

	// ������ ������ �ִ� ������Ʈ ����
	auto Capacity = origin.components.capacity();
	components.resize(Capacity);

	for (auto new_component : origin.components)
	{
		components.push_back(new_component);
	}

	return *this;
}

// �̵����� ������
GameObject& GameObject::operator=(GameObject&& origin) noexcept
{
	if (this != &origin)
	{
		*this = origin;

		// ���� ��ü clear
		for (auto component : origin.components)
		{
			if (component != nullptr)
			{
				component->Destroy();
				component = nullptr;
			}
		}
		origin.name.clear();
		origin.pos = Vec2();
		origin.scale = Vec2();
	}

	return *this;
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
	Engine::GetInstance().Render(*this);
}