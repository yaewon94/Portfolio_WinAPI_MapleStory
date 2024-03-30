#include "PCH.h"
#include "GameObject.h"
#include "Engine.h"
#include "Component.h"

// 생성자
GameObject::GameObject(const wstring& name, Vec2 pos, Vec2 scale)
	: name(name), pos(pos), scale(scale)
{
}

// 복사 생성자
GameObject::GameObject(const GameObject& origin) : Entity(origin)//, GameObject(origin.name, origin.pos, origin.scale)
, name(origin.name), pos(origin.pos), scale(origin.scale)
{
	auto Capacity = origin.components.capacity();
	components.resize(Capacity);

	for (auto i=0; i<Capacity; ++i)
	{
		// [check] 하위 타입을 알아내야 함
		//this->components[i] = new T(origin.components[i]);
		this->components[i] = origin.components[i]->Clone();
	}
}

// 소멸자
GameObject::~GameObject()
{
	for (auto component : components)
	{
		if (component != nullptr)
		{
			delete component;
			component = nullptr;
		}
	}
}

// 렌더링 (매 프레임마다 호출)
void GameObject::Render()
{
	Engine::GetInstance().Render(*this);
}