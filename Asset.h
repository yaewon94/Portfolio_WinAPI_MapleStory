#pragma once
#include "Entity.h"

// �̹���, ���� �� ���� ��ü�� �����ϴ� ���ҽ��� ���� ��ü
// [abstract class]
class Asset : public Entity
{
	NO_CSTR_COPY_ASSIGN(Asset);

protected:
	wstring key;
	wstring relativePath;

	Asset(const wstring& key, const wstring& relativePath);
	~Asset();

public:
	virtual int Load(const wstring& key) = 0;
};