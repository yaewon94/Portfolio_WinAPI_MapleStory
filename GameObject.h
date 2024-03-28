#pragma once
#include "Entity.h"

// �÷��̾�, ����, UI ���� ��ӹ޴� �ֻ��� Ŭ����
// abstract class
class GameObject : public Entity
{
protected:
	Vec2 pos;
	Vec2 scale;

public:
	GameObject(const wstring& name, Vec2 pos, Vec2 Scale);
	GameObject(const GameObject& origin);
	virtual ~GameObject();

	virtual void Render() override final;
};