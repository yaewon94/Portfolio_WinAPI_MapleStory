#pragma once

typedef int RandomResult;

// ������ ���� Ŭ����
class RandomManager final
{
	NO_CSTR_COPY_ASSIGN(RandomManager);

private:
	RandomManager() {}
	~RandomManager() {}

public:
	static RandomResult Create(int mod);
};