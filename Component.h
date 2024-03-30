#pragma once
#include "Entity.h"

class GameObject;

// ���� ������Ʈ�� ������ �ִ� ������Ʈ �ֻ��� Ŭ����
// abstract class
class Component : public Entity
{
protected:
	GameObject* owner;
	
public:
	Component(GameObject* owner);
	Component(const Component& origin);
	~Component();

	virtual Component* Clone() = 0;
};