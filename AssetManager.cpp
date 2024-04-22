#include "PCH.h"
#include "AssetManager.h"
#include "PathManager.h"
#include "SoundManager.h"
#include "Sound.h"
#include "Texture.h"

// 생성자
AssetManager::AssetManager()
{
}

// 소멸자
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

// 초기화
void AssetManager::Init()
{
	SoundManager::GetInstance().Init();
	// [CHECK] 아예 Init()에서 모든 에셋을 등록해버릴지, 
	// 아니면 별도 함수에서 레벨마다 필요한 에셋만 등록할지
}

// 이미지 생성
Texture* AssetManager::CreateTexture(const wstring& key, UINT width, UINT height)
{
	// map에 이미 등록된 에셋인 경우
	Texture* texture = FindTexture(key);
	if (texture != nullptr)
	{
		Log(LOG_TYPE::LOG_ERROR, L"이미 생성된 에셋입니다");
		return texture;
	}

	// 텍스처 생성
	texture = new Texture(key);
	if (FAILED(texture->Create(width, height)))
	{
		Log(LOG_TYPE::LOG_ERROR, L"텍스처 생성 실패");
		delete texture;
		return nullptr;
	}

	// map에 등록
	textureMap.insert(make_pair(key, texture));

	return texture;
}

// 이미지 로드
Texture* AssetManager::LoadTexture(const wstring& key, const wstring& relativePath)
{
	// map에 등록된 에셋이 있는 경우
	Texture* texture = FindTexture(key);
	if (texture != nullptr) return texture;

	// 없는 경우
	// 절대 경로 얻기
	wstring absolutePath = PathManager::GetInstance().GetContentPath();
	absolutePath += L"\\Assets\\Textures\\";
	absolutePath += relativePath;

	// 텍스처 객체 로드
	texture = new Texture(key, relativePath);
	if (FAILED(texture->Load(absolutePath)))
	{
		Log(LOG_TYPE::LOG_ERROR, L"텍스처 로딩 실패");
		delete texture;
		return nullptr;
	}

	// map에 등록
	textureMap.insert(make_pair(key, texture));

	return texture;
}

// 사운드 로딩
Sound* AssetManager::LoadSound(const wstring& key, const wstring& relativePath)
{
	// map에 등록된 에셋이 있는 경우
	Sound* sound = FindSound(key);
	if (sound != nullptr) return sound;

	// 없는 경우
	// 절대 경로 얻기
	wstring absolutePath = PathManager::GetInstance().GetContentPath();
	absolutePath += L"\\Assets\\Sounds\\";
	absolutePath += relativePath;

	// 사운드 객체 생성
	sound = new Sound(key, relativePath);
	if (FAILED(sound->Load(absolutePath)))
	{
		Log(LOG_TYPE::LOG_ERROR, L"사운드 로딩 실패");
		delete sound;
		return nullptr;
	}

	// map에 등록
	soundMap.insert(make_pair(key, sound));

	return sound;
}

// 이미지 찾기
Texture* AssetManager::FindTexture(const wstring& key)
{
	auto iter = textureMap.find(key);

	if (iter != textureMap.end()) return iter->second;
	else return nullptr;
}

// 사운드 찾기
Sound* AssetManager::FindSound(const wstring& key)
{
	auto iter = soundMap.find(key);

	if (iter != soundMap.end()) return iter->second;
	else return nullptr;
}