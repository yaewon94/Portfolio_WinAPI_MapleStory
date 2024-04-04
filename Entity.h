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

	const UINT ID;

public:
	const UINT GetID() const { return ID; }

	virtual void Init() = 0;
	virtual void Tick() = 0;
	virtual void FinalTick() = 0;
	//virtual void Render() = 0;
};