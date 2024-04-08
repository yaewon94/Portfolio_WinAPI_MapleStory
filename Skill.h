#pragma once

struct Skill
{
private:
	static UINT nextID;

private:
	const UINT ID;
	wstring* name;

	NO_CSTR_COPY_ASSIGN(Skill);
	Skill(const wstring& name);
	~Skill();
};