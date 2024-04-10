#pragma once

class Texture;

class AssetManager final
{
	SINGLETON(AssetManager);

private:
	map<wstring, Texture*> textureMap;

public:
	void Init();

	Texture* LoadTexture(const wstring& key, const wstring& relativePath);
};