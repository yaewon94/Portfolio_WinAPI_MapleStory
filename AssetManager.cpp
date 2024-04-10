#include "PCH.h"
#include "AssetManager.h"
#include "PathManager.h"
#include "Texture.h"

// ������
AssetManager::AssetManager()
{
}

// �Ҹ���
AssetManager::~AssetManager()
{
	for (auto& pair : textureMap)
	{
		if (pair.second != nullptr)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}
}

// �ʱ�ȭ
void AssetManager::Init()
{
	// [CHECK] �ƿ� Init()���� ��� ������ ����ع�����, 
	// �ƴϸ� ���� �Լ����� �������� �ʿ��� ���¸� �������
}

// �̹��� �ε�
Texture* AssetManager::LoadTexture(const wstring& key, const wstring& relativePath)
{
	// map�� ��ϵ� ������ �ִ� ���
	auto iter = textureMap.find(key);
	if (iter != textureMap.end()) return iter->second;

	// ���� ���
	// ���� ��� ���
	wstring absolutePath = PathManager::GetInstance().GetContentPath();
	absolutePath += relativePath;

	// �ؽ�ó ��ü �ε�
	Texture* texture = new Texture(key, relativePath);
	if (FAILED(texture->Load(absolutePath)))
	{
		Log(LOG_TYPE::LOG_ERROR, L"�ؽ�ó �ε� ����");
		delete texture;
		return nullptr;
	}

	// map�� ���
	textureMap.insert(make_pair(key, texture));

	return texture;
}