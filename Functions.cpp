#include "PCH.h"
#include "Functions.h"

// inline ���̴ϱ� ������ ������

// ========== ���ڿ� ó�� ==========
wstring to_wstring(const string& str)
{
	wstring wstr;
	wstr.assign(str.begin(), str.end());
	return wstr;
}
