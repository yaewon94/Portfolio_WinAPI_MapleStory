#include "PCH.h"
#include "Texture.h"

// 생성자
Texture::Texture(const wstring& key, const wstring& relativePath) : Asset(key, relativePath)
{
}

// 소멸자
Texture::~Texture()
{
}

// 에셋 로드
int Texture::Load(const wstring& key)
{
	return 0;
}