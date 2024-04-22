#include "PCH.h"
#include "Animation.h"
#include "Animator.h"
#include "AliveObject.h"
#include "Engine.h"
#include "FSM.h"
#include "Texture.h"
#include "TimeManager.h"

// ������
Animation::Animation(Animator* animator, Texture* atlasTex, int frameCount, bool isRepeat, float duration)
	: animator(animator), atlasTex(atlasTex), frameCount(frameCount), isRepeat(isRepeat), duration(duration)
{
	// �� �����Ӻ� ���� ���� (��� ����)
	int widthPerFrame = atlasTex->GetWidth() / frameCount;

	// �� �����Ӻ� �̹��� ũ�� (��� ����)
	// �� ������ �̹����� ���� �������θ�(row=n, col=1) �迭�Ǿ��ٰ� ����
	scale = Vec2(widthPerFrame, atlasTex->GetHeight());

	// ��ǥ ����
	for (int i = 0; i < frameCount; ++i)
	{
		Vec2<int> offset = Vec2<int>(widthPerFrame * i, 0);
		offsets.push_back(offset);
	}
}

// ���� ������
Animation::Animation(const Animation& origin)
	: Entity(origin), atlasTex(origin.atlasTex), frameCount(origin.frameCount), isRepeat(origin.isRepeat)
	, offsets(origin.offsets), scale(origin.scale), duration(origin.duration)
	, animator(nullptr)
{
	// animator �ʱ�ȭ�� Animator ���� �����ڿ��� ���
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

	curTime += TimeManager::GetInstance().GetDeltaTime();

	// �����Ӵ� ��� �ð��� ������ ���� ���������� �ٲ���
	if(curTime >= duration)
	{
		curTime -= duration;

		// ������ �������� ���
		if (++curFrame == offsets.size())
		{
			// ������ �ε��� �ʱ�ȭ
			curFrame = 0;

			// �ݺ������ �ƴ� ���
			if (!isRepeat)
			{
				FSM* fsm = animator->GetOwner()->GetComponent<FSM>();
				if (fsm != nullptr) fsm->ChangeState(fsm->GetDefaultState());
				else animator->GetOwner()->SetActive(false);
			}
		}
	}
}

// ������ (�� �����Ӹ��� ȣ��)
void Animation::Render()
{
	// ������Ʈ ��ġ
	Vec2 objPos = animator->GetOwner()->GetRenderPos();
	atlasTex->Render((int)(objPos.x - scale.x * 0.5f), (int)(objPos.y - scale.y * 0.5f)
		, scale.x, scale.y
		, offsets[curFrame].x, offsets[curFrame].y
		, scale.x, scale.y);
}