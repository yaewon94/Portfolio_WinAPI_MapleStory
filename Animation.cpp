#include "PCH.h"
#include "Animation.h"
#include "Animator.h"
#include "AliveObject.h"
#include "Engine.h"
#include "FSM.h"
#include "Texture.h"
#include "TimeManager.h"

// 생성자
Animation::Animation(Animator* animator, Texture* atlasTex, int frameCount, bool isRepeat, float duration) 
	: animator(animator), atlasTex(atlasTex), frameCount(frameCount), isRepeat(isRepeat), duration(duration)
	, curFrame(0)
{
	// 각 프레임별 가로 길이 (모두 동일)
	int widthPerFrame = atlasTex->GetWidth() / frameCount;

	// 각 프레임별 이미지 크기 (모두 동일)
	// 각 프레임 이미지가 가로 방향으로만(row=n, col=1) 배열되었다고 가정
	scale = Vec2(widthPerFrame, atlasTex->GetHeight());
	
	// 좌표 설정
	for (int i = 0; i < frameCount; ++i)
	{
		Vec2<int> offset = Vec2<int>(widthPerFrame*i, 0);
		offsets.push_back(offset);
	}
}

// 복사 생성자
Animation::Animation(const Animation& origin) 
	: Entity(origin), atlasTex(origin.atlasTex), frameCount(origin.frameCount), isRepeat(origin.isRepeat)
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
	if (frameCount == 1) return;

	static float time = 0;
	time += TimeManager::GetInstance().GetDeltaTime();

	// 프레임당 재생 시간이 지나면 다음 프레임으로 바꿔줌
	if (time >= duration)
	{
		time = 0;

		// 마지막 프레임일 경우
		if (++curFrame == offsets.size())
		{
			curFrame = 0;
			if(!isRepeat) animator->GetOwner()->GetComponent<FSM>()->ChangeState(OBJECT_STATE::IDLE);
		}
	}
}

// 렌더링 (매 프레임마다 호출)
void Animation::Render()
{
	assert(atlasTex);

	// 이미지 사이즈에 맞게 크기 변경
	GameObject* obj = animator->GetOwner();

	//HDC& mainDC = Engine::GetInstance().GetMainDC();
	//Vec2 resolution = Engine::GetInstance().GetResolution();
	Vec2 objPos = obj->GetRenderPos();
	//Vec2 objScale = obj->GetScale();
	//float dir = ((AliveObject*)animator->GetOwner())->GetDirection().x;

	// png 이미지
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
		, (int)(objPos.x - scale.x * 0.5f), (int)(objPos.y - scale.y * 0.5f)
		, scale.x, scale.y
		, atlasTex->GetDC()
		, offsets[curFrame].x, offsets[curFrame].y
		, scale.x, scale.y
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