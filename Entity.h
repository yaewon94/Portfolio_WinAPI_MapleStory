#pragma once

// ���� ���� ��� ������Ʈ, ������Ʈ ���� ��ӹ޴� �ֻ��� Ŭ����
// abstract class
class Entity
{
private:
	static UINT nextID;

protected:
	const UINT ID;

	Entity();
	Entity(const Entity& origin);
	virtual ~Entity();

public:
	virtual void Init() = 0;
	virtual void Tick() = 0;
	virtual void FinalTick() = 0;
	//virtual void Render() = 0;
};