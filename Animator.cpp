#include "PCH.h"
#include "Animator.h"
#include "Animation.h"

// 생성자
Animator::Animator() : curAnim(nullptr)
{
}

Animator::Animator(GameObject& owner) : Component(owner), curAnim(nullptr)
{
}

// 복사 생성자
Animator::Animator(const Animator& origin) : Component(origin), curAnim(nullptr)
{
	for (auto& pair : origin.animMap)
	{
		Animation* anim = pair.second->Clone();
		anim->SetAnimator(*this);
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
	if(curAnim != nullptr) curAnim->FinalTick();
}

// 렌더링 (매 프레임마다 호출)
void Animator::Render()
{
	if(curAnim != nullptr) curAnim->Render();
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
	if (curAnim != nullptr) curAnim->curFrame = 0;	// 현재 애니메이션의 인덱스 초기화
	Animation* anim = FindAnimation(key);

	if (anim == nullptr)
	{
		Log(LOG_TYPE::LOG_ERROR, L"애니메이션이 존재하지 않습니다");
		return;
	}

	curAnim = anim;
}

// 상태 - 애니메이션 맵 설정
// 하나의 스킬오브젝트로 각각 다른 스킬을 쓸때 애니메이션 바꾸는 용도
void Animator::SetAnimationMap(map<OBJECT_STATE, Animation*>& animMap, OBJECT_STATE defaultState)
{
	this->animMap = animMap;
	for (auto& pair : this->animMap)
	{
		pair.second->SetAnimator(*this);
	}

	curAnim = animMap.find(defaultState)->second;
}

// 애니메이션 찾기
Animation* Animator::FindAnimation(OBJECT_STATE key)
{
	auto iter = animMap.find(key);

	if (iter != animMap.end()) return iter->second;
	else return nullptr;
}