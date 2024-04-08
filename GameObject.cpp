#include "PCH.h"
#include "GameObject.h"
#include "Engine.h"
#include "Component.h"
#include "Camera.h"

// static 멤버 초기화
Camera* GameObject::mainCamera = nullptr;

// 생성자
GameObject::GameObject(const wstring& name, Vec2 pos, Vec2 scale, LAYER_TYPE layer)
	: name(name), pos(pos), scale(scale), layer(layer)
{
}

// 복사 생성자
GameObject::GameObject(const GameObject& origin)
	: Entity(origin), name(origin.name), pos(origin.pos), scale(origin.scale), layer(origin.layer)
{
	// 원본이 가지고 있는 컴포넌트 복사
	for (auto component : origin.components)
	{
		components.push_back(component->Clone());
	}

	// 카메라 제거 x (Level 소멸자에서 제거됨)
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
	Engine::GetInstance().Render(mainCamera->GetRenderPos(this->pos), this->scale);
}