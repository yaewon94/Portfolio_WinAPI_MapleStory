#pragma once

typedef int RandomResult;

// 랜덤값 관리 클래스
class RandomManager final
{
	NO_CSTR_COPY_ASSIGN(RandomManager);

private:
	RandomManager() {}
	~RandomManager() {}

public:
	static RandomResult Create(int mod);
};