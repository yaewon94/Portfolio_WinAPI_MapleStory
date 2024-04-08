#include "PCH.h"
#include "GameObject.h"
#include "Engine.h"
#include "Component.h"
#include "Camera.h"

// static ��� �ʱ�ȭ
Camera* GameObject::mainCamera = nullptr;

// ������
GameObject::GameObject(const wstring& name, Vec2 pos, Vec2 scale, LAYER_TYPE layer)
	: name(name), pos(pos), scale(scale), layer(layer)
{
}

// ���� ������
GameObject::GameObject(const GameObject& origin)
	: Entity(origin), name(origin.name), pos(origin.pos), scale(origin.scale), layer(origin.layer)
{
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
	Engine::GetInstance().Render(mainCamera->GetRenderPos(this->pos), this->scale);
}