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
	vector<Vec2> offsets;	// 아틀라스 텍스처에서 각 프레임의 좌상단 좌표
	Vec2 scale;				// 각 프레임의 이미지 크기 (모두 동일)
	float duration;			// 각 프레임당 재생 시간 (모두 동일)

	int curFrame;

private:
	friend class Animator;

	Animator* animator;

	Animation(Animator* animator, Texture* atlasTex, int frameCount, float duration=1.f);
	Animation(const Animation& origin);
	~Animation();
	virtual Animation* Clone() override { return new Animation(*this); }

	void FinalTick();
	void Render();
};