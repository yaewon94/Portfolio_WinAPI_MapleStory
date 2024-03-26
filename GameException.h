#pragma once

#include <stdexcept>
using std::exception;

// 게임 관련 예외처리 클래스
class GameException : exception
{
public:
	GameException(const wstring& Message);
	~GameException();
};