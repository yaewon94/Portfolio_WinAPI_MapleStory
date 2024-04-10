#include "PCH.h"
#include "PathManager.h"

// ������
PathManager::PathManager()
{
}

// �Ҹ���
PathManager::~PathManager()
{
}

// �ʱ�ȭ
void PathManager::Init()
{
	// ���� �������� ��θ� ����
	wchar_t path[256] = {};
	GetCurrentDirectory(256, path);

	// bin ������ ���������� �����Ѵ�.
	GetParentPath(path);

	// ������ ��� ����
	contentPath = path;
	contentPath += L"\\contents\\";
}

// �θ� ��� ��ȯ
void PathManager::GetParentPath(wchar_t* path)
{
	size_t length = wcslen(path);

	for (size_t i=length-1; i>0; --i)
	{
		// ��� ������
		if (path[i] == L'\\')
		{
			path[i] = L'\0';	// ���ڿ��� ������ ������ش�
			break;
		}
	}
}
