#pragma once

// ���� ���� ��� ������Ʈ, ������Ʈ ���� ��ӹ޴� �ֻ��� Ŭ����
// abstract class
class Entity
{
private:
	static UINT nextID;

protected:
	CSTR_COPY_ASSIGN(Entity);
	Entity();
	virtual ~Entity();

	const UINT ID;

public:
	virtual void Init() = 0;
	virtual void Tick() = 0;
	virtual void FinalTick() = 0;
	//virtual void Render() = 0;
};