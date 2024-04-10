#include "PCH.h"
#include "Texture.h"

// ������
Texture::Texture(const wstring& key, const wstring& relativePath) 
	: Asset(key, relativePath)
	, hSubDC(nullptr), hBitmap(nullptr), bitmapInfo{}
{
}

// �Ҹ���
Texture::~Texture()
{
	DeleteDC(hSubDC);
	DeleteObject(hBitmap);
}

// ���� �ε�
int Texture::Load(const wstring& key)
{
	return 0;
}