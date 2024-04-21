#pragma once
#include "Component.h"
#include "Animation.h"

class Texture;

// �ִϸ��̼��� �����Ű�� ������Ʈ
class Animator final : public Component
{
private:
	map<OBJECT_STATE, Animation*> animMap;
	Animation* curAnim;

public:
	Animator();
	Animator(GameObject& owner);
	Animator(const Animator& origin);
	~Animator();
	virtual Animator* Clone() override { return new Animator(*this); }

	virtual void FinalTick() override;
	void Render();

	void AddAnimation(OBJECT_STATE key, Texture* atlasTex, int frameCount, bool isRepeat=true);
	void ChangeAnimation(OBJECT_STATE key);
	void SetAnimationMap(map<OBJECT_STATE, Animation*>& animMap, OBJECT_STATE defaultState);
	void ClearAnimationMap() { animMap.clear(); }
	void ResetAnimationIndex() { if (curAnim != nullptr) curAnim->curFrame = 0; }

private:
	Animation* FindAnimation(OBJECT_STATE key);
};