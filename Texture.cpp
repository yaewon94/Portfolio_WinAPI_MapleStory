#include "PCH.h"
#include "Texture.h"
#include "Engine.h"

// 생성자
Texture::Texture(const wstring& key, const wstring& relativePath) 
	: Asset(key, relativePath)
	, subDC(nullptr), hBitmap(nullptr), bitmapInfo{}
{
}

// 소멸자
Texture::~Texture()
{
	DeleteDC(subDC);
	DeleteObject(hBitmap);
}

// 에셋 생성
int Texture::Create(UINT width, UINT height)
{
    HDC mainDC = Engine::GetInstance().GetMainDC();

    // DC 생성
    subDC = CreateCompatibleDC(mainDC);

    // Bitmap 생성
    hBitmap = CreateCompatibleBitmap(mainDC, width, height);

    // SubDC 가 SubBitmap 을 지정하게 함
    DeleteObject(SelectObject(subDC, hBitmap));

    // 로드된 비트맵의 정보를 확인한다.
    GetObject(hBitmap, sizeof(BITMAP), &bitmapInfo);

    return S_OK;
}

// 에셋 로드
int Texture::Load(const wstring& absolutePath)
{
	// 확장자 판별
	wchar_t extType[50] = {};
	_wsplitpath_s(absolutePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, extType, 50);

    // .png 파일인 경우
    if (!wcscmp(extType, L".png") || !wcscmp(extType, L".PNG"))
    {
        ULONG_PTR gdiPlusToken = 0;
        GdiplusStartupInput gdiPlusInput = {};
        GdiplusStartup(&gdiPlusToken, &gdiPlusInput, nullptr);

        Image* image = Image::FromFile(absolutePath.c_str());
        Bitmap* bitmap = (Bitmap*)image->Clone();
        Gdiplus::Status status = bitmap->GetHBITMAP(Color(0, 0, 0, 0), &hBitmap);

        if (status != Gdiplus::Status::Ok)
        {
            Log(LOG_TYPE::LOG_ERROR, L"png 파일 로딩 실패");
            return E_FAIL;
        }
    }
    else
    {
        Log(LOG_TYPE::LOG_ERROR, L"확장자 타입이 png가 아닙니다");
        return E_FAIL;
    }

    // 로드된 비트맵 정보 확인
    GetObject(hBitmap, sizeof(BITMAP), &bitmapInfo);

    // DC 생성
    subDC = CreateCompatibleDC(Engine::GetInstance().GetMainDC());

    // SubDC 가 SubBitmap 을 지정하게 함
    DeleteObject(SelectObject(subDC, hBitmap));

    return S_OK;
}

// 이미지 렌더링
void Texture::Render(int x, int y, int width, int height, int rscX, int rscY, int rscWidth, int rscHeight)
{
	assert(this);

	// png 이미지
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	/*
	// ERROR : 좌우반전은 되는데 몇초지나면 이미지 사라짐
	HDC strectchDC = CreateCompatibleDC(mainDC);
	HBITMAP stretchBit = CreateCompatibleBitmap(mainDC, resolution.x, resolution.y);
	SelectObject(strectchDC, stretchBit);

	StretchBlt(Engine::GetInstance().GetSubDC()
		, (int)objPos.x, (int)objPos.y
		, (int)(scale.x * dir), (int)scale.y
		, atlasTex->GetDC()
		, (int)offsets[curFrame].x, (int)offsets[curFrame].y
		, (int)scale.x, (int)scale.y
		, SRCCOPY);
	*/

	if (rscWidth == 0) rscWidth = bitmapInfo.bmWidth;
	if (rscHeight == 0) rscHeight = bitmapInfo.bmHeight;
	
	AlphaBlend(Engine::GetInstance().GetSubDC()
		, x, y
		, width, height
		, this->GetDC()
		, rscX, rscY
		, rscWidth, rscHeight
		, bf);

	//DeleteObject(stretchBit);
	//DeleteDC(strectchDC);

	/*
	// 비트맵 이미지
	TransparentBlt(Engine::GetInstance().GetSubDC()
		, (int)objPos.x, (int)objPos.y
		, (int)scale.x, (int)scale.y
		, atlasTex->GetDC()
		, (int)offsets[curFrame].x, (int)offsets[curFrame].y
		, (int)scale.x, (int)scale.y
		, RGB(255, 0, 255));
	*/
}