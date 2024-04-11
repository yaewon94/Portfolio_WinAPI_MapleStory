#pragma once

// 게임 내의 모든 오브젝트, 컴포넌트 등이 상속받는 최상위 클래스
// abstract class
class Entity
{
private:
	static UINT nextID;

protected:
	Entity();
	Entity(const Entity& origin);
	virtual ~Entity();
	virtual Entity* Clone() = 0;

	const UINT ID;

public:
	const UINT GetID() const { return ID; }
};