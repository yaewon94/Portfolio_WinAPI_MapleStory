#include "PCH.h"
#include "Log.h"

// ������
Log::Log(LOG_TYPE type, wstring message, Vec2<float> renderPos) 
	: type(type), message(message), renderPos(renderPos)
{
}

// �Ҹ���
Log::~Log()
{
}