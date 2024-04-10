#include "PCH.h"
#include "Texture.h"

// 생성자
Texture::Texture(const wstring& key, const wstring& relativePath) 
	: Asset(key, relativePath)
	, hSubDC(nullptr), hBitmap(nullptr), bitmapInfo{}
{
}

// 소멸자
Texture::~Texture()
{
	DeleteDC(hSubDC);
	DeleteObject(hBitmap);
}

// 에셋 로드
int Texture::Load(const wstring& key)
{
	return 0;
}