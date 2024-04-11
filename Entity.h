#pragma once

// ���� ���� ��� ������Ʈ, ������Ʈ ���� ��ӹ޴� �ֻ��� Ŭ����
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