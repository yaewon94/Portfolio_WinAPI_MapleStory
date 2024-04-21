#include "PCH.h"
#include "Animator.h"
#include "Animation.h"

// ������
Animator::Animator() : curAnim(nullptr)
{
}

Animator::Animator(GameObject& owner) : Component(owner), curAnim(nullptr)
{
}

// ���� ������
Animator::Animator(const Animator& origin) : Component(origin), curAnim(nullptr)
{
	for (auto& pair : origin.animMap)
	{
		Animation* anim = pair.second->Clone();
		anim->SetAnimator(*this);
		animMap.insert(make_pair(pair.first, anim));
	}
}

// �Ҹ���
Animator::~Animator()
{
	curAnim = nullptr;

	for (auto& pair : animMap)
	{
		if (pair.second != nullptr)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}
}

// �� �����Ӹ��� ȣ��
void Animator::FinalTick()
{
	if(curAnim != nullptr) curAnim->FinalTick();
}

// ������ (�� �����Ӹ��� ȣ��)
void Animator::Render()
{
	if(curAnim != nullptr) curAnim->Render();
}

// �ִϸ��̼� �߰�
void Animator::AddAnimation(OBJECT_STATE key, Texture* atlasTex, int frameCount, bool isRepeat)
{
	if (FindAnimation(key) != nullptr)
	{
		Log(LOG_TYPE::LOG_ERROR, L"�̹� �ش� KEY���� ���� �ִϸ��̼��� �����մϴ�");
		return;
	}

	Animation* anim = new Animation(this, atlasTex, frameCount, isRepeat);
	animMap.insert(make_pair(key, anim));
}

// �ִϸ��̼� ����
void Animator::ChangeAnimation(OBJECT_STATE key)
{
	if (curAnim != nullptr) curAnim->curFrame = 0;	// ���� �ִϸ��̼��� �ε��� �ʱ�ȭ
	Animation* anim = FindAnimation(key);

	if (anim == nullptr)
	{
		Log(LOG_TYPE::LOG_ERROR, L"�ִϸ��̼��� �������� �ʽ��ϴ�");
		return;
	}

	curAnim = anim;
}

// ���� - �ִϸ��̼� �� ����
// �ϳ��� ��ų������Ʈ�� ���� �ٸ� ��ų�� ���� �ִϸ��̼� �ٲٴ� �뵵
void Animator::SetAnimationMap(map<OBJECT_STATE, Animation*>& animMap, OBJECT_STATE defaultState)
{
	this->animMap = animMap;
	for (auto& pair : this->animMap)
	{
		pair.second->SetAnimator(*this);
	}

	curAnim = animMap.find(defaultState)->second;
}

// �ִϸ��̼� ã��
Animation* Animator::FindAnimation(OBJECT_STATE key)
{
	auto iter = animMap.find(key);

	if (iter != animMap.end()) return iter->second;
	else return nullptr;
}