#pragma once
#include "Asset.h"

// 이미지 리소스
class Texture final : public Asset
{
	friend class AssetManager;

	NO_CSTR_COPY_ASSIGN(Texture);

private:
	HDC hDC;
	HBITMAP hBitmap;
	BITMAP bitmapInfo;

	Texture(const wstring& key, const wstring& relativePath);
	~Texture();

	virtual int Load(const wstring& absolutePath) override;
};