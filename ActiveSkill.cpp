#include "PCH.h"
#include "ActiveSkill.h"

// 생성자
ActiveSkill::ActiveSkill(const wstring& name, KEY_CODE keyCode) : Skill(name), keyCode(keyCode)
{
	// TODO : 키코드 중복되지 않게 해야함
}

// 소멸자
ActiveSkill::~ActiveSkill()
{
}