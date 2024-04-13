#include "PCH.h"
#include "Animator.h"
#include "Animation.h"

// ������
Animator::Animator(GameObject& owner) : Component(owner), curAnim(nullptr)
{
}

// ���� ������
Animator::Animator(const Animator& origin) : Component(origin), curAnim(nullptr)
{
	for (auto& pair : origin.animMap)
	{
		Animation* anim = pair.second->Clone();
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
	assert(curAnim);
	curAnim->FinalTick();
}

// ������ (�� �����Ӹ��� ȣ��)
void Animator::Render()
{
	assert(curAnim);
	curAnim->Render();
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
	Animation* anim = FindAnimation(key);

	if (anim == nullptr)
	{
		Log(LOG_TYPE::LOG_ERROR, L"�ִϸ��̼��� �������� �ʽ��ϴ�");
		return;
	}

	curAnim = anim;
}

// �ִϸ��̼� ã��
Animation* Animator::FindAnimation(OBJECT_STATE key)
{
	auto iter = animMap.find(key);

	if (iter != animMap.end()) return iter->second;
	else return nullptr;
}