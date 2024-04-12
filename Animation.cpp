#include "PCH.h"
#include "Animation.h"
#include "Animator.h"
#include "AliveObject.h"
#include "Engine.h"
#include "Texture.h"
#include "TimeManager.h"

// ������
Animation::Animation(Animator* animator, Texture* atlasTex, int frameCount, float duration) 
	: animator(animator), atlasTex(atlasTex), frameCount(frameCount), duration(duration)
	, curFrame(0)
{
	// �� �����Ӻ� ���� ���� (��� ����)
	float widthPerFrame = (float)(atlasTex->GetWidth() / frameCount);

	// �� �����Ӻ� �̹��� ũ�� (��� ����)
	// �� ������ �̹����� ���� �������θ�(row=n, col=1) �迭�Ǿ��ٰ� ����
	scale = Vec2(widthPerFrame, (float)atlasTex->GetHeight());
	
	// ��ǥ ����
	for (int i = 0; i < frameCount; ++i)
	{
		Vec2 offset = Vec2(widthPerFrame*i, 0.f);
		offsets.push_back(offset);
	}
}

// ���� ������
Animation::Animation(const Animation& origin) 
	: Entity(origin), atlasTex(origin.atlasTex), frameCount(origin.frameCount)
	, offsets(origin.offsets), scale(origin.scale), duration(origin.duration)
	, curFrame(0)
	, animator(nullptr)
{
}

// �Ҹ���
Animation::~Animation()
{
	atlasTex = nullptr;
	animator = nullptr;
}

// �� �����Ӹ��� ȣ��
void Animation::FinalTick()
{
	if (frameCount == 1) return;

	static float time = 0;
	time += TimeManager::GetInstance().GetDeltaTime();

	// �����Ӵ� ��� �ð��� ������ ���� ���������� �ٲ���
	if (time >= duration)
	{
		time = 0;

		// ������ �������� ���, ó�� �����Ӻ��� �ݺ�
		if (++curFrame == offsets.size()) curFrame = 0;
	}
}

// ������ (�� �����Ӹ��� ȣ��)
void Animation::Render()
{
	assert(atlasTex);

	// �̹��� ����� �°� ũ�� ����
	GameObject* obj = animator->GetOwner();

	//HDC& mainDC = Engine::GetInstance().GetMainDC();
	//Vec2 resolution = Engine::GetInstance().GetResolution();
	Vec2 objPos = obj->GetRenderPos();
	//float dir = ((AliveObject*)animator->GetOwner())->GetDirection().x;

	// png �̹���
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	/*
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
		, (int)objPos.x, (int)objPos.y
		, (int)scale.x, (int)scale.y
		, atlasTex->GetDC()
		, (int)offsets[curFrame].x, (int)offsets[curFrame].y
		, (int)scale.x, (int)scale.y
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