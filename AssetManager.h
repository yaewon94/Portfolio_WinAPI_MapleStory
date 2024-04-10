#pragma once

class Texture;

class AssetManager final
{
	SINGLETON(AssetManager);

private:
	map<wstring, Texture*> textureMap;

public:
	void Init();

	Texture* CreateTexture(const wstring& key, UINT width, UINT height);
	Texture* LoadTexture(const wstring& key, const wstring& relativePath);

private:
	Texture* FindTexture(const wstring& key);
};