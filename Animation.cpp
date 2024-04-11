#include "PCH.h"
#include "Animation.h"
#include "Animator.h"
#include "Engine.h"
#include "GameObject.h"
#include "Texture.h"
#include "TimeManager.h"

// ������
Animation::Animation(Texture* atlasTex, int frameCount, float duration) 
	: atlasTex(atlasTex), frameCount(frameCount),  duration(duration)
	, curFrame(0)
	, animator(nullptr)
{
	// ũ��
	// �� ������ �̹����� ���� �������θ�(row=n, col=1) �迭�Ǿ��ٰ� ����
	scale = Vec2((float)atlasTex->GetWidth() / frameCount, (float)atlasTex->GetHeight());

	// ��ǥ ����
	for (int i = 0; i < frameCount; ++i)
	{
		offsets.push_back(scale * i);
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

	Vec2 objPos = animator->GetOwner()->GetRenderPos();

	// png �̹���
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 0;
	bf.AlphaFormat = 0;

	AlphaBlend(Engine::GetInstance().GetSubDC()
		, (int)objPos.x, (int)objPos.y
		, (int)scale.x, (int)scale.y
		, atlasTex->GetDC()
		, (int)offsets[curFrame].x, (int)offsets[curFrame].y
		, (int)scale.x, (int)scale.y
		, bf);

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