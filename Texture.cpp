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