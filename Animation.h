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
	vector<Vec2> offsets;	// ��Ʋ�� �ؽ�ó���� �� �������� �»�� ��ǥ
	Vec2 scale;				// �� �������� �̹��� ũ�� (��� ����)
	float duration;			// �� �����Ӵ� ��� �ð� (��� ����)

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