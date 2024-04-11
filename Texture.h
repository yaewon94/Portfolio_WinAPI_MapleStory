#pragma once
#include "Asset.h"

// �̹��� ���ҽ�
class Texture final : public Asset
{
	friend class AssetManager;

	NO_CSTR_COPY_ASSIGN(Texture);

private:
	HDC hDC;
	HBITMAP hBitmap;
	BITMAP bitmapInfo;

	Texture(const wstring& key, const wstring& relativePath=L"");
	~Texture();
	virtual Texture* Clone() override { return nullptr; }

	int Create(UINT width, UINT height);
	virtual int Load(const wstring& absolutePath) override;

public:
	HDC GetDC() { return hDC; }
};