#pragma once

class Sound;
class Texture;

// ���� ���� Ŭ����
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