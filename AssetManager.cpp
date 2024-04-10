#include "PCH.h"
#include "AssetManager.h"
#include "PathManager.h"
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
	// [CHECK] 아예 Init()에서 모든 에셋을 등록해버릴지, 
	// 아니면 별도 함수에서 레벨마다 필요한 에셋만 등록할지
}

// 이미지 로드
Texture* AssetManager::LoadTexture(const wstring& key, const wstring& relativePath)
{
	// map에 등록된 에셋이 있는 경우
	auto iter = textureMap.find(key);
	if (iter != textureMap.end()) return iter->second;

	// 없는 경우
	// 절대 경로 얻기
	wstring absolutePath = PathManager::GetInstance().GetContentPath();
	absolutePath += relativePath;

	// 텍스처 객체 로드
	Texture* texture = new Texture(key, relativePath);
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