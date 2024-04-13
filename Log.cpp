#include "PCH.h"
#include "Log.h"

// 持失切
Log::Log(LOG_TYPE type, wstring message, Vec2<float> renderPos) 
	: type(type), message(message), renderPos(renderPos)
{
}

// 社瑚切
Log::~Log()
{
}