#pragma once
#include "Asset.h"

// �̹��� ���ҽ�
class Texture final : public Asset
{
	friend class AssetManager;

	NO_CSTR_COPY_ASSIGN(Texture);

private:
	HDC subDC;
	HBITMAP hBitmap;
	BITMAP bitmapInfo;

	Vec2<float> renderRatio = Vec2(1.f, 1.f);	// ����� ũ�� ���� (���ҽ� ��� ����)
	Vec2<float> sliceRatio = Vec2(1.f, 1.f);	// ���� ���ҽ����� �߶� ����� ����

	Texture(const wstring& key, const wstring& relativePath=L"");
	~Texture();

	int Create(UINT width, UINT height);
	virtual int Load(const wstring& absolutePath) override;

public:
	HDC& GetDC() { return subDC; }
	int GetWidth() const { return bitmapInfo.bmWidth; }
	int GetHeight() const { return bitmapInfo.bmHeight; }

	void SetRenderRatio(float x, float y);
	void SetSliceRatio(float x, float y);

	void Render(int x, int y, int width, int height);
	void Render(int x, int y, int width, int height, int rscX, int rscY, int rscWidth, int rscHeight);
};