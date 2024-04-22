#include "PCH.h"
#include "SkillObject.h"
#include "Animation.h"
#include "Animator.h"
#include "AttackSkillModule.h"
#include "Collider.h"
#include "Skill.h"
#include "SkillManager.h"
#include "TimeManager.h"

// 생성자
SkillObject::SkillObject(const wstring& name, GameObject& caster, Vec2<float> offset, Vec2<int> scale, LAYER_TYPE layer)
	: GameObject(name, offset, scale, layer, false)
	, caster(caster), Offset(offset)
	, attackSkillPtr(nullptr), skillPtr(nullptr)
{
	if (layer == LAYER_TYPE::PLAYER_SKILL || layer == LAYER_TYPE::ENEMY_SKILL) {}
	else throw std::invalid_argument("invalid layer type");	// 객체 생성 취소
}

// 복사 생성자
// ERROR : caster 설정하는데 문제있어서 쓰면안됌
SkillObject::SkillObject(const SkillObject& origin) 
	: GameObject(origin)
	//, caster(nullptr) //, caster(origin.caster)
	, caster(origin.caster)
	, Offset(origin.offset), velocity(origin.velocity), startPos(origin.startPos)
	, attackSkillPtr(origin.attackSkillPtr), skillPtr(origin.skillPtr)
{
}

// 소멸자
SkillObject::~SkillObject()
{
	attackSkillPtr = nullptr;
	skillPtr = nullptr;

	// 애니메이터에 있는 애니메이션 초기화
	GetComponent<Animator>()->ClearAnimationMap();

	// 스킬 애니메이션 제거
	for (auto& skillPair : skillMap)
	{
		for (auto& state_anim_pair : skillPair.second)
		{
			if (state_anim_pair.second != nullptr)
			{
				delete state_anim_pair.second;
				state_anim_pair.second = nullptr;
			}
		}
	}
}

// 초기화
void SkillObject::Init()
{
	// 컴포넌트 추가
	AddComponent<Collider>();
	AddComponent<Animator>();

	// 담당 스킬들 관련 초기화
	for (auto& skillPair : skillMap)
	{
		// 스킬 애니메이션 map 복제
		Skill& skill = SkillManager::GetInstance().GetSkill(skillPair.first);
		for (auto& state_anim_pair : skill.GetAnimationMap())
		{
			skillPair.second.insert(make_pair(state_anim_pair.first, state_anim_pair.second->Clone()));
		}
	}

	// 스킬 애니메이션 변경
	if (skillPtr != nullptr)
	{
		auto iter = skillMap.find(skillPtr->GetIndex());
		auto& pair = skillMap.find(skillPtr->GetIndex())->second;
		if (pair.size() > 0) GetComponent<Animator>()->SetAnimationMap(pair, skillPtr->GetObjectState());
	}

	// 최상위 부모 Init() 호출
	GameObject::Init();
}

// 매 프레임마다 호출
void SkillObject::Tick()
{
	float dt = TimeManager::GetInstance().GetDeltaTime();
	time += dt;

	// 스킬오브젝트 활성화 시간이 지나면 비활성화
	if (time >= attackSkillPtr->GetDuration())
	{
		time = 0.f;
		SetActive(false);
		return;
	}
	// 최대 이동거리를 넘어섰을 경우
	if (GetRealPos() - startPos > velocity)
	{
		// 지속시간 제한이 따로 없는 경우 비활성화
		if (attackSkillPtr->GetDuration() == NO_LIMIT_DURATION)
		{
			time = 0.f;
			SetActive(false);
			return;
		}
		else
		{
			return;
		}
	}
	// 또는 상대방에게 맞았을 때 비활성화 (이건 외부에서 처리함)

	// 세가지 조건에 해당하지 않으면 스킬오브젝트 이동
	Vec2<float> curPos = GetRealPos() + velocity * attackSkillPtr->GetSpeed() * TimeManager::GetInstance().GetDeltaTime();
	SetRealPos(curPos);
}

// 충돌 시작
void SkillObject::OnCollisionEnter(GameObject& other)
{
	//if (other.GetLayer() == LAYER_TYPE::ENEMY) SetActive(false);
}

// 스킬오브젝트가 담당하는 스킬들 추가
void SkillObject::AddSkill(int index)
{
	map<OBJECT_STATE, Animation*> map;
	skillMap.insert(make_pair(index, map));
}

// 현재 사용할 스킬 설정
void SkillObject::SetSkill(AttackSkillModule* me_attack, Skill* me_skill)
{
	SetSkill(me_attack, me_skill, me_attack->GetMaxRange());
}

void SkillObject::SetSkill(AttackSkillModule* me_attack, Skill* me_skill, Vec2<float> velocity)
{
	if (skillPtr == me_skill) return;

	attackSkillPtr = me_attack;
	skillPtr = me_skill;
	this->velocity = velocity;
	auto iter = skillMap.find(me_skill->GetIndex());
	auto& pair = skillMap.find(me_skill->GetIndex())->second;

	// 스킬 애니메이션 변경
	if (pair.size() > 0) GetComponent<Animator>()->SetAnimationMap(pair, me_skill->GetObjectState());
}

// 스킬오브젝트 활성화,비활성화
void SkillObject::SetActive(bool flag)
{
	GameObject::SetActive(flag);

	if (flag)
	{
		// 현재 애니메이션 인덱스 0으로 설정
		GetComponent<Animator>()->ResetAnimationIndex();

		// 시전자를 기준으로 시작좌표 설정
		startPos = caster.GetRealPos() + Offset;
		SetRealPos(startPos);
	}
	else
	{
		// 현재 애니메이션 인덱스 0으로 설정
		//GetComponent<Animator>()->ResetAnimationIndex();

		// 콜백함수가 있으면 호출
		if (skillPtr != nullptr) skillPtr->OnDisappear(this);
	}
}
