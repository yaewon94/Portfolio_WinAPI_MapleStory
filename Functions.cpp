#include "PCH.h"
#include "Functions.h"

// inline 먹이니까 컴파일 에러남

// ========== 문자열 처리 ==========
wstring to_wstring(const string& str)
{
	wstring wstr;
	wstr.assign(str.begin(), str.end());
	return wstr;
}
