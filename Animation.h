#pragma once
#include "Entity.h"

class Animator;
class Texture;

// 애니메이션 클래스
class Animation final : public Entity
{
private:
	Texture* atlasTex;	// 모든 프레임의 이미지를 보유하고 있는 아틀라스 텍스처
	int frameCount;
	vector<Vec2<int>> offsets;		// 아틀라스 텍스처에서 각 프레임의 좌상단 좌표
	Vec2<int> scale;				// 각 프레임의 이미지 크기 (모두 동일)
	float duration;					// 각 프레임당 재생 시간 (모두 동일)
	bool isRepeat;

	int curFrame = 0;		// 현재 프레임 인덱스
	float curTime = 0.f;	// 현재 프레임 재생 후 경과시간

private:
	friend class Animator;

	Animator* animator;

	Animation(Animator* animator, Texture* atlasTex, int frameCount, bool isRepeat=true, float duration= DEFAULT_ANIM_DURATION);
	Animation(const Animation& origin);
	~Animation();
	virtual Animation* Clone() override { return new Animation(*this); }
	
	void SetAnimator(Animator& animator) { this->animator = &animator; }

	void FinalTick();
	void Render();
};