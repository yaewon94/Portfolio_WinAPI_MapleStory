#include "PCH.h"
#include "GameObject.h"
#include "Engine.h"
#include "LevelManager.h"
#include "Camera.h"
#include "Component.h"

// static 멤버 초기화
Camera* GameObject::mainCamera = nullptr;

// 생성자
GameObject::GameObject(const wstring& name, Vec2 offset, Vec2 scale, LAYER_TYPE layer)
	: name(name), offset(offset), scale(scale), layer(layer), parent(nullptr)
{
}

// 복사 생성자
GameObject::GameObject(const GameObject& origin)
	: Entity(origin)
	, name(origin.name), offset(origin.offset), scale(origin.scale), layer(origin.layer), parent(origin.parent)
{
	// 원본이 가지고 있는 자식 오브젝트 복사
	for (auto child : origin.children)
	{
		children.push_back(child->Clone());
	}

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
	parent = nullptr;

	// 자식 오브젝트 삭제
	DeleteChildren();
	
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

// 부모 오브젝트 설정
void GameObject::SetParent(GameObject& parent)
{
	// 현재 레벨에 등록된 오브젝트인지 확인
	if (LevelManager::GetInstance().FindObject(parent) == nullptr)
	{
		Log(LOG_TYPE::LOG_ERROR, L"현재 레벨에 존재하는 오브젝트가 아닙니다");
		return;
	}

	// 부모 - 자식 설정
	this->parent = &parent;
	parent.AddChild(*this);
}

// 자식 오브젝트 추가
void GameObject::AddChild(GameObject& child)
{
	children.push_back(&child);
	child.parent = this;

	// 현재 레벨의 오브젝트 목록에 등록
	if (LevelManager::GetInstance().FindObject(child) == nullptr)
	{
		LevelManager::GetInstance().AddObject(child);
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
	Engine::GetInstance().Render(mainCamera->GetRenderPos(this->offset), this->scale);
}

// 자식 오브젝트 삭제
void GameObject::DeleteChildren()
{
	for (auto child : children)
	{
		if (child != nullptr)
		{
			// 현재 레벨에 등록된 오브젝트 목록에서 삭제
			LevelManager::GetInstance().DeleteObject(*child);

			// 실제 객체 삭제
			delete child;
			child = nullptr;
		}
	}
}