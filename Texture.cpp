#include "PCH.h"
#include "Texture.h"

// ������
Texture::Texture(const wstring& key, const wstring& relativePath) : Asset(key, relativePath)
{
}

// �Ҹ���
Texture::~Texture()
{
}

// ���� �ε�
int Texture::Load(const wstring& key)
{
	return 0;
}