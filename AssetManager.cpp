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

// �̹��� ����
Texture* AssetManager::CreateTexture(const wstring& key, UINT width, UINT height)
{
	// map�� �̹� ��ϵ� ������ ���
	Texture* texture = FindTexture(key);
	if (texture != nullptr)
	{
		Log(LOG_TYPE::LOG_ERROR, L"�̹� ������ �����Դϴ�");
		return texture;
	}

	// �ؽ�ó ����
	texture = new Texture(key);
	if (FAILED(texture->Create(width, height)))
	{
		Log(LOG_TYPE::LOG_ERROR, L"�ؽ�ó ���� ����");
		delete texture;
		return nullptr;
	}

	// map�� ���
	textureMap.insert(make_pair(key, texture));

	return texture;
}

// �̹��� �ε�
Texture* AssetManager::LoadTexture(const wstring& key, const wstring& relativePath)
{
	// map�� ��ϵ� ������ �ִ� ���
	Texture* texture = FindTexture(key);
	if (texture != nullptr) return texture;

	// ���� ���
	// ���� ��� ���
	wstring absolutePath = PathManager::GetInstance().GetContentPath();
	absolutePath += relativePath;

	// �ؽ�ó ��ü �ε�
	texture = new Texture(key, relativePath);
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

// �̹��� ã��
Texture* AssetManager::FindTexture(const wstring& key)
{
	auto iter = textureMap.find(key);

	if (iter != textureMap.end()) return iter->second;
	else return nullptr;
}