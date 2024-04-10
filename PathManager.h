#pragma once

// ��� ���� Ŭ����
class PathManager final
{
	SINGLETON(PathManager);

private:
	wstring contentPath;

public:
	void Init();
	const wstring& GetContentPath() { return contentPath; }

private:
	void GetParentPath(wchar_t* path);
};