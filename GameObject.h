#pragma once
#include "Entity.h"

// 플레이어, 몬스터, UI 등이 상속받는 최상위 클래스
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