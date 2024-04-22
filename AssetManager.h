#pragma once

class Sound;
class Texture;

// 에셋 관리 클래스
class AssetManager final
{
	SINGLETON(AssetManager);

private:
	map<wstring, Texture*> textureMap;
	map<wstring, Sound*> soundMap;

public:
	void Init();

	Texture* CreateTexture(const wstring& key, UINT width, UINT height);
	Texture* LoadTexture(const wstring& key, const wstring& relativePath=L"");
	Sound* LoadSound(const wstring& key, const wstring& relativePath = L"");

private:
	Texture* FindTexture(const wstring& key);
	Sound* FindSound(const wstring& key);
};