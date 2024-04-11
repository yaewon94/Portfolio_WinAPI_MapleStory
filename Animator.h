#pragma once
#include "Component.h"

class Animation;

// �ִϸ��̼��� �����Ű�� ������Ʈ
class Animator final : public Component
{
private:
	map<OBJECT_STATE, Animation*> animMap;
	Animation* curAnim;

public:
	Animator(GameObject& owner);
	Animator(const Animator& origin);
	~Animator();
	virtual Animator* Clone() override { return new Animator(*this); }

	virtual void FinalTick() override;
	void Render();

	void AddAnimation(OBJECT_STATE key, Animation& anim);
	void ChangeAnimation(OBJECT_STATE key);

private:
	Animation* FindAnimation(OBJECT_STATE key);
};