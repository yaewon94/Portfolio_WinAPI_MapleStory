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
		Vec2<int> offset = Vec2<int>(widthPerFrame * i, 0);
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
	// animator 초기화는 Animator 복사 생성자에서 담당
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
			if (!isRepeat)
			{
				FSM* fsm = animator->GetOwner()->GetComponent<FSM>();
				fsm->ChangeState(fsm->GetDefaultState());
			}
		}
	}
}

// 렌더링 (매 프레임마다 호출)
void Animation::Render()
{
	// 오브젝트 위치
	Vec2 objPos = animator->GetOwner()->GetRenderPos();
	atlasTex->Render((int)(objPos.x - scale.x * 0.5f), (int)(objPos.y - scale.y * 0.5f)
		, scale.x, scale.y
		, offsets[curFrame].x, offsets[curFrame].y
		, scale.x, scale.y);
}