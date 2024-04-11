#pragma once
#include "Asset.h"

// 이미지 리소스
class Texture final : public Asset
{
	friend class AssetManager;

	NO_CSTR_COPY_ASSIGN(Texture);

private:
	HDC subDC;
	HBITMAP hBitmap;
	BITMAP bitmapInfo;

	Texture(const wstring& key, const wstring& relativePath=L"");
	~Texture();
	virtual Texture* Clone() override { return nullptr; }

	int Create(UINT width, UINT height);
	virtual int Load(const wstring& absolutePath) override;

public:
	HDC GetDC() { return subDC; }
	int GetWidth() const { return bitmapInfo.bmWidth; }
	int GetHeight() const { return bitmapInfo.bmHeight; }
};