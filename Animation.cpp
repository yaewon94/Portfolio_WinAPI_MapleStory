#include "PCH.h"
#include "Animation.h"
#include "Animator.h"
#include "Engine.h"
#include "GameObject.h"
#include "Texture.h"
#include "TimeManager.h"

// 생성자
Animation::Animation(Texture* atlasTex, int frameCount, float duration) 
	: atlasTex(atlasTex), frameCount(frameCount),  duration(duration)
	, curFrame(0)
	, animator(nullptr)
{
	// 크기
	// 각 프레임 이미지가 가로 방향으로만(row=n, col=1) 배열되었다고 가정
	scale = Vec2((float)atlasTex->GetWidth() / frameCount, (float)atlasTex->GetHeight());

	// 좌표 설정
	for (int i = 0; i < frameCount; ++i)
	{
		offsets.push_back(scale * i);
	}
}

// 복사 생성자
Animation::Animation(const Animation& origin) 
	: Entity(origin), atlasTex(origin.atlasTex), frameCount(origin.frameCount)
	, offsets(origin.offsets), scale(origin.scale), duration(origin.duration)
	, curFrame(0)
	, animator(nullptr)
{
}

// 소멸자
Animation::~Animation()
{
	atlasTex = nullptr;
	animator = nullptr;
}

// 매 프레임마다 호출
void Animation::FinalTick()
{
	static float time = 0;
	time += TimeManager::GetInstance().GetDeltaTime();

	// 프레임당 재생 시간이 지나면 다음 프레임으로 바꿔줌
	if (time >= duration)
	{
		time = 0;

		// 마지막 프레임일 경우, 처음 프레임부터 반복
		if (++curFrame == offsets.size()) curFrame = 0;
	}
}

// 렌더링 (매 프레임마다 호출)
void Animation::Render()
{
	assert(atlasTex);

	Vec2 objPos = animator->GetOwner()->GetRenderPos();

	// png 이미지
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