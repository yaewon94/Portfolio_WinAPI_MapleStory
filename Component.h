#pragma once
#include "Entity.h"

class GameObject;

// 게임 오브젝트가 가지고 있는 컴포넌트 최상위 클래스
// abstract class
class Component : public Entity
{
private:
	GameObject* owner;

protected:
	CSTR_COPY_ASSIGN(Component);
	Component(GameObject& owner);
	~Component();

public:
	void Destroy();
	virtual Component* Clone() = 0;

	GameObject* GetOwner() { return owner; }

	// [check] 임시
	virtual void Init() override {}
	virtual void Tick() override {}
};

// 컴포넌트 삭제
inline void Component::Destroy()
{
	if (this != nullptr) delete this;
}