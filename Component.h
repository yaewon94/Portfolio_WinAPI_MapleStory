#pragma once
#include "Entity.h"

class GameObject;

// 게임 오브젝트가 가지고 있는 컴포넌트 최상위 클래스
// abstract class
class Component : public Entity
{
private:
	GameObject* owner;

public:
	Component(GameObject& owner);
	Component(const Component& origin);
	Component(Component&& origin) noexcept;
	~Component();

	Component& operator=(const Component& origin);
	Component& operator=(Component&& origin) noexcept;
	virtual Component* Clone() = 0;

	GameObject* GetOwner() { return owner; }
};