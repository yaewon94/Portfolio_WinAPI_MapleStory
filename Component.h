#pragma once
#include "Entity.h"

class GameObject;

// 게임 오브젝트가 가지고 있는 컴포넌트 최상위 클래스
// abstract class
class Component : public Entity
{
private:
	GameObject* owner;
	bool isActive = true;

protected:
	Component();
	Component(GameObject& owner);
	Component(const Component& origin);
	~Component();

public:
	void Destroy();
	virtual Component* Clone() = 0;

	GameObject* GetOwner() const { return owner; }
	void SetOwner(GameObject& owner) { this->owner = &owner; }
	bool IsActive() { return isActive; }
	void SetActive(bool flag) { isActive = flag; }

	virtual void Init() {}
	virtual void FinalTick() {}
};

// 컴포넌트 삭제
inline void Component::Destroy()
{
	if (this != nullptr) delete this;
}