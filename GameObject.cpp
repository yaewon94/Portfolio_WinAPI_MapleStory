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
GameObject::GameObject(const GameObject& origin) : Entity(origin)
, name(origin.name), pos(origin.pos), scale(origin.scale)
{
	*this = origin;
}

// 이동 생성자
GameObject::GameObject(GameObject&& origin) noexcept : Entity(std::move(origin))
{
	*this = std::move(origin);
}

// 소멸자
GameObject::~GameObject()
{
	// 컴포넌트 삭제
	for (auto component : components)
	{
		if (component != nullptr)
		{
			component->Destroy();
			component = nullptr;
		}
	}
}

// 대입 연산자
GameObject& GameObject::operator=(const GameObject& origin)
{
	name = origin.name;
	pos = origin.pos;
	scale = origin.scale;
	
	// 기존 컴포넌트 clear
	for (auto component : components)
	{
		if (component != nullptr)
		{
			component->Destroy();
			component = nullptr;
		}
	}

	// 원본이 가지고 있는 컴포넌트 복사
	auto Capacity = origin.components.capacity();
	components.resize(Capacity);

	for (auto new_component : origin.components)
	{
		components.push_back(new_component);
	}

	return *this;
}

// 이동대입 연산자
GameObject& GameObject::operator=(GameObject&& origin) noexcept
{
	if (this != &origin)
	{
		*this = origin;

		// 원본 객체 clear
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

// 매 프레임마다 호출
void GameObject::FinalTick()
{
	for (auto component : components)
	{
		component->FinalTick();
	}
}

// 렌더링 (매 프레임마다 호출)
void GameObject::Render()
{
	Engine::GetInstance().Render(*this);
}