#pragma once
#include "Entity.h"

class Animator;
class Texture;

// �ִϸ��̼� Ŭ����
class Animation final : public Entity
{
private:
	Texture* atlasTex;	// ��� �������� �̹����� �����ϰ� �ִ� ��Ʋ�� �ؽ�ó
	int frameCount;
	vector<Vec2<int>> offsets;		// ��Ʋ�� �ؽ�ó���� �� �������� �»�� ��ǥ
	Vec2<int> scale;				// �� �������� �̹��� ũ�� (��� ����)
	float duration;					// �� �����Ӵ� ��� �ð� (��� ����)
	bool isRepeat;

	int curFrame;

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