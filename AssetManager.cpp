#include "PCH.h"
#include "AssetManager.h"
#include "PathManager.h"
#include "SoundManager.h"
#include "Sound.h"
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
	SoundManager::GetInstance().Init();
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
	absolutePath += L"\\Assets\\Textures\\";
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

// ���� �ε�
Sound* AssetManager::LoadSound(const wstring& key, const wstring& relativePath)
{
	// map�� ��ϵ� ������ �ִ� ���
	Sound* sound = FindSound(key);
	if (sound != nullptr) return sound;

	// ���� ���
	// ���� ��� ���
	wstring absolutePath = PathManager::GetInstance().GetContentPath();
	absolutePath += L"\\Assets\\Sounds\\";
	absolutePath += relativePath;

	// ���� ��ü ����
	sound = new Sound(key, relativePath);
	if (FAILED(sound->Load(absolutePath)))
	{
		Log(LOG_TYPE::LOG_ERROR, L"���� �ε� ����");
		delete sound;
		return nullptr;
	}

	// map�� ���
	soundMap.insert(make_pair(key, sound));

	return sound;
}

// �̹��� ã��
Texture* AssetManager::FindTexture(const wstring& key)
{
	auto iter = textureMap.find(key);

	if (iter != textureMap.end()) return iter->second;
	else return nullptr;
}

// ���� ã��
Sound* AssetManager::FindSound(const wstring& key)
{
	auto iter = soundMap.find(key);

	if (iter != soundMap.end()) return iter->second;
	else return nullptr;
}