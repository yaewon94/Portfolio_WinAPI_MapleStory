#include "PCH.h"
#include "Functions.h"

// inline ���̴ϱ� ������ ������

// ========== ���ڿ� ó�� ==========
wstring to_wstring(Vec2 vec)
{
	return std::to_wstring(vec.x) + L" , " + std::to_wstring(vec.y);
}