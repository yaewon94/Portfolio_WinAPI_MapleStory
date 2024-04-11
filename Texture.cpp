#include "PCH.h"
#include "Texture.h"
#include "Engine.h"

// ������
Texture::Texture(const wstring& key, const wstring& relativePath) 
	: Asset(key, relativePath)
	, subDC(nullptr), hBitmap(nullptr), bitmapInfo{}
{
}

// �Ҹ���
Texture::~Texture()
{
	DeleteDC(subDC);
	DeleteObject(hBitmap);
}

// ���� ����
int Texture::Create(UINT width, UINT height)
{
    HDC mainDC = Engine::GetInstance().GetMainDC();

    // DC ����
    subDC = CreateCompatibleDC(mainDC);

    // Bitmap ����
    hBitmap = CreateCompatibleBitmap(mainDC, width, height);

    // SubDC �� SubBitmap �� �����ϰ� ��
    DeleteObject(SelectObject(subDC, hBitmap));

    // �ε�� ��Ʈ���� ������ Ȯ���Ѵ�.
    GetObject(hBitmap, sizeof(BITMAP), &bitmapInfo);

    return S_OK;
}

// ���� �ε�
int Texture::Load(const wstring& absolutePath)
{
	// Ȯ���� �Ǻ�
	wchar_t extType[50] = {};
	_wsplitpath_s(absolutePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, extType, 50);

    // .png ������ ���
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
            Log(LOG_TYPE::LOG_ERROR, L"png ���� �ε� ����");
            return E_FAIL;
        }
    }
    else
    {
        Log(LOG_TYPE::LOG_ERROR, L"Ȯ���� Ÿ���� png�� �ƴմϴ�");
        return E_FAIL;
    }

    // �ε�� ��Ʈ�� ���� Ȯ��
    GetObject(hBitmap, sizeof(BITMAP), &bitmapInfo);

    // DC ����
    subDC = CreateCompatibleDC(Engine::GetInstance().GetMainDC());

    // SubDC �� SubBitmap �� �����ϰ� ��
    DeleteObject(SelectObject(subDC, hBitmap));

    return S_OK;
}