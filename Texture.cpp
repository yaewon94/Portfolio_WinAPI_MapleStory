#include "PCH.h"
#include "Texture.h"
#include "Engine.h"

// ������
Texture::Texture(const wstring& key, const wstring& relativePath) 
	: Asset(key, relativePath)
	, hDC(nullptr), hBitmap(nullptr), bitmapInfo{}
{
}

// �Ҹ���
Texture::~Texture()
{
	DeleteDC(hDC);
	DeleteObject(hBitmap);
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

    // DC - ��Ʈ�� ����
    Engine::GetInstance().ConnectDC(hDC, hBitmap);

    return S_OK;
}