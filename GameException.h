#pragma once

#include <stdexcept>
using std::exception;

// ���� ���� ����ó�� Ŭ����
class GameException : exception
{
public:
	GameException(const wstring& Message);
	~GameException();
};