#include "PCH.h"
#include "PathManager.h"

// 생성자
PathManager::PathManager()
{
}

// 소멸자
PathManager::~PathManager()
{
}

// 초기화
void PathManager::Init()
{
	// 게임 실행파일 경로를 얻어낸다
	wchar_t path[256] = {};
	GetCurrentDirectory(256, path);

	// bin 폴더의 상위폴더로 접근한다.
	GetParentPath(path);

	// 콘텐츠 경로 설정
	contentPath = path;
	contentPath += L"\\contents\\";
}

// 부모 경로 반환
void PathManager::GetParentPath(wchar_t* path)
{
	size_t length = wcslen(path);

	for (size_t i=length-1; i>0; --i)
	{
		// 경로 구분자
		if (path[i] == L'\\')
		{
			path[i] = L'\0';	// 문자열의 끝으로 만들어준다
			break;
		}
	}
}
