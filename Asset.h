#pragma once
#include "Entity.h"

// 이미지, 사운드 등 여러 객체가 공유하는 리소스의 상위 객체
// [abstract class]
class Asset : public Entity
{
	NO_CSTR_COPY_ASSIGN(Asset);

protected:
	wstring key;
	wstring relativePath;

	Asset(const wstring& key, const wstring& relativePath);
	~Asset();

	virtual int Load(const wstring& absolutePath) = 0;
};