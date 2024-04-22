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

	Vec2<float> offset = Vec2(0.f, 0.f);		// 게임오브젝트에서 이미지의 상대적 위치
	Vec2<float> renderRatio = Vec2(1.f, 1.f);	// 출력할 크기 비율 (리소스 모양 유지)
	Vec2<float> sliceRatio = Vec2(1.f, 1.f);	// 현재 리소스에서 잘라서 출력할 비율
	int alpha = MAX_ALPHA;

	Texture(const wstring& key, const wstring& relativePath=L"");
	~Texture();

	int Create(UINT width, UINT height);
	virtual int Load(const wstring& absolutePath) override;

public:
	HDC& GetDC() { return subDC; }
	int GetWidth() const { return bitmapInfo.bmWidth; }
	int GetHeight() const { return bitmapInfo.bmHeight; }

	void SetOffset(float x, float y);
	void SetRenderRatio(float x, float y);
	void SetSliceRatio(float x, float y);
	void SetAlpha(int alpha) { this->alpha = alpha; }

	void Render(int x, int y, int width, int height);
	void Render(int x, int y, int width, int height, int rscX, int rscY, int rscWidth, int rscHeight);
};