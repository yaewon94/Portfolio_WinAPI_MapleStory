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

// ����� ũ�� ���� ����
void Texture::SetRenderRatio(float x, float y)
{
	renderRatio.x = x;
	renderRatio.y = y;
}

// ���ҽ����� �߶� ����ϱ� ���ϴ� �κ� ���� ����
void Texture::SetSliceRatio(float x, float y)
{
	sliceRatio.x = x;
	sliceRatio.y = y;
	SetRenderRatio(x, y);
}

// �̹��� ������
void Texture::Render(int x, int y, int width, int height)
{
	Render(x, y, width, height, 0, 0, bitmapInfo.bmWidth, bitmapInfo.bmHeight);
}

void Texture::Render(int x, int y, int width, int height, int rscX, int rscY, int rscWidth, int rscHeight)
{
	assert(this);

	// png �̹���
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	/*
	// ERROR : �¿������ �Ǵµ� ���������� �̹��� �����
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

	AlphaBlend(Engine::GetInstance().GetSubDC()
		, x, y
		, width * renderRatio.x, height * renderRatio.y
		//, width * sliceRatio.x, height * sliceRatio.y
		, this->GetDC()
		, rscX, rscY
		, rscWidth * sliceRatio.x, rscHeight * sliceRatio.y
		, bf);

	//DeleteObject(stretchBit);
	//DeleteDC(strectchDC);

	/*
	// ��Ʈ�� �̹���
	TransparentBlt(Engine::GetInstance().GetSubDC()
		, (int)objPos.x, (int)objPos.y
		, (int)scale.x, (int)scale.y
		, atlasTex->GetDC()
		, (int)offsets[curFrame].x, (int)offsets[curFrame].y
		, (int)scale.x, (int)scale.y
		, RGB(255, 0, 255));
	*/
}