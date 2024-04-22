#include "PCH.h"
#include "Skill.h"
#include "Animation.h"

// 생성자
Skill::Skill(const wstring& name) : name(name)
{
}

// 소멸자
Skill::~Skill()
{
	for (auto& pair : animMap)
	{
		if (pair.second != nullptr)
		{
			// ERROR : 잘못설계
			// 여기서 지워야되는데, 스킬오브젝트에 스킬이 할당된 상태면
			// 스킬오브젝트 소멸자->애니메이터 컴포넌트 소멸자->애니메이션 소멸자 호출 되서 지워짐
			delete pair.second;
			pair.second = nullptr;
		}
	}

	animMap.clear();
}

// 스킬오브젝트 사라질때 콜백
void Skill::OnDisappear(GameObject* obj)
{
	if(on_disappear != nullptr) on_disappear(obj);
}