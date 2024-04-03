#pragma once

// 게임 내의 모든 오브젝트, 컴포넌트 등이 상속받는 최상위 클래스
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