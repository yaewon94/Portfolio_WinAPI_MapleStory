#include "PCH.h"
#include "GameObject.h"
#include "Animator.h"
#include "Engine.h"
#include "LevelManager.h"
#include "Camera.h"
#include "Component.h"
#include "Texture.h"

// 생성자
GameObject::GameObject(LAYER_TYPE layer) : layer(layer), isActive(true), texture(nullptr), parent(nullptr)
{
}

GameObject::GameObject(const wstring& name, Vec2<float> offset, Vec2<int> scale, LAYER_TYPE layer, bool isActive)
	: name(name), offset(offset), scale(scale), layer(layer),isActive(isActive)
	, texture(nullptr), parent(nullptr)
{
}

// 복사 생성자
GameObject::GameObject(const GameObject& origin)
	: Entity(origin)
	, name(origin.name), offset(origin.offset), scale(origin.scale)
	, layer(origin.layer), isActive(origin.isActive), texture(origin.texture)
	, parent(origin.parent)
{
	// 원본이 가지고 있는 자식 오브젝트 복사
	for (auto& layer : origin.children)
	{
		for (auto child : layer)
		{
			AddChild(*child->Clone());
		}
	}

	// 원본이 가지고 있는 컴포넌트 복사
	for (auto component : origin.components)
	{
		Component* clone = component->Clone();
		clone->SetOwner(*this);
		components.push_back(clone);
		// ERROR : 컴포넌트 복사 에러
		//components.push_back(component->Clone());
	}
}

// 소멸자
GameObject::~GameObject()
{

	// Texture 객체 제거는 AssetManager 담당
	texture = nullptr;

	// 부모 오브젝트는 지우면 안됌
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

// 렌더링 좌표 가져오기
Vec2<float> GameObject::GetRenderPos()
{
	Vec2 realPos = GetRealPos();
	return Level::GetMainCamera().GetRenderPos(realPos);
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

// 필드 값 설정
void GameObject::Set(Vec2<float> offset, Vec2<int> scale)
{
	this->offset = offset;
	this->scale = scale;
}

// 오브젝트 활성화/비활성화
void GameObject::SetActive(bool flag)
{
	// 컴포넌트 활성화/비활성화
	for (auto component : components)
	{
		component->SetActive(flag);
	}

	// 필드값 설정
	isActive = flag;

	// 자식 오브젝트는 선택적으로 활성화/비활성화
}

// 자식 오브젝트 추가
GameObject* GameObject::AddChild(GameObject& child)
{
	children[(size_t)child.GetLayer()].push_back(&child);
	child.parent = this;

	// 현재 레벨의 오브젝트 목록에 등록
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

	// 현재 레벨의 오브젝트 목록에 등록
	LevelManager::GetInstance().AddObject(*clone);

	return clone;
}

// 초기화
void GameObject::Init()
{
	for (auto component : components)
	{
		component->Init();
	}

	SetActive(isActive);
}

// 매 프레임마다 호출
void GameObject::FinalTick()
{
	for (auto component : components)
	{
		if (component->IsActive()) component->FinalTick();
	}
}

// 렌더링 (매 프레임마다 호출)
void GameObject::Render()
{
	Animator* animator = GetComponent<Animator>();
	if (animator != nullptr) animator->Render();
	else if (texture != nullptr)
	{
		texture->Render((int)(GetRenderPos().x - scale.x * 0.5f), (int)(GetRenderPos().y - scale.y * 0.5f), scale.x, scale.y);
	}
}

// 자식 오브젝트 삭제
void GameObject::DeleteChildren()
{
	for (auto& layer : children)
	{

		for (auto child : layer)
		{
			// 현재 레벨에 등록된 오브젝트 목록에서 삭제
			LevelManager::GetInstance().DeleteObjectFromList(*child);

			// 실제 객체 삭제
			//delete child;
			child->Destroy();
			child = nullptr;

		}
	}
}