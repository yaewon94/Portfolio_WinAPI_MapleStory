#include "PCH.h"
#include "Animator.h"
#include "Animation.h"

// 생성자
Animator::Animator(GameObject& owner) : Component(owner), curAnim(nullptr)
{
}

// 복사 생성자
Animator::Animator(const Animator& origin) : Component(origin), curAnim(nullptr)
{
	for (auto& pair : origin.animMap)
	{
		Animation* anim = pair.second->Clone();
		animMap.insert(make_pair(pair.first, anim));
	}
}

// 소멸자
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

// 매 프레임마다 호출
void Animator::FinalTick()
{
	assert(curAnim);
	curAnim->FinalTick();
}

// 렌더링 (매 프레임마다 호출)
void Animator::Render()
{
	assert(curAnim);
	curAnim->Render();
}

// 애니메이션 추가
void Animator::AddAnimation(OBJECT_STATE key, Texture* atlasTex, int frameCount, bool isRepeat)
{
	if (FindAnimation(key) != nullptr)
	{
		Log(LOG_TYPE::LOG_ERROR, L"이미 해당 KEY값을 가진 애니메이션이 존재합니다");
		return;
	}

	Animation* anim = new Animation(this, atlasTex, frameCount, isRepeat);
	animMap.insert(make_pair(key, anim));
}

// 애니메이션 변경
void Animator::ChangeAnimation(OBJECT_STATE key)
{
	Animation* anim = FindAnimation(key);

	if (anim == nullptr)
	{
		Log(LOG_TYPE::LOG_ERROR, L"애니메이션이 존재하지 않습니다");
		return;
	}

	curAnim = anim;
}

// 애니메이션 찾기
Animation* Animator::FindAnimation(OBJECT_STATE key)
{
	auto iter = animMap.find(key);

	if (iter != animMap.end()) return iter->second;
	else return nullptr;
}