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
	, caster(caster), Offset(offset), skill(nullptr)
{
	if (layer == LAYER_TYPE::PLAYER_SKILL || layer == LAYER_TYPE::ENEMY_SKILL) {}
	else throw std::invalid_argument("invalid layer type");	// 객체 생성 취소
}

// 복사 생성자
SkillObject::SkillObject(const SkillObject& origin) 
	: GameObject(origin)
	, caster(origin.caster), Offset(origin.offset), skill(origin.skill)
{
}

// 소멸자
SkillObject::~SkillObject()
{
	skill = nullptr;

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

	// 최상위 부모 Init() 호출
	GameObject::Init();
}

// 매 프레임마다 호출
void SkillObject::Tick()
{
	float dt = TimeManager::GetInstance().GetDeltaTime();
	time += dt;

	// 스킬오브젝트 활성화 시간이 지나거나
	// 최대 이동거리를 넘어서면 자동으로 비활성화
	// 또는 상대방에게 맞았을 때 비활성화 (이건 외부에서 처리함)
	if (time >= skill->GetDuration()
		|| GetRealPos() - startPos > skill->GetMaxRange())
	{
		time = 0.f;
		SetActive(false);
		return;
	}

	Vec2<float> curPos = GetRealPos() + skill->GetMaxRange() * skill->GetSpeed() * TimeManager::GetInstance().GetDeltaTime();
	SetRealPos(curPos);
}

// 충돌 시작
void SkillObject::OnCollisionEnter(GameObject& other)
{
	if (other.GetLayer() == LAYER_TYPE::ENEMY) SetActive(false);
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
	if (this->skill == me_attack) return;

	this->skill = me_attack;
	auto& pair = skillMap.find(me_skill->GetIndex())->second;

	// 스킬 애니메이션 변경
	if(pair.size() > 0) GetComponent<Animator>()->SetAnimationMap(pair, me_skill->GetObjectState());
}

// 스킬오브젝트 활성화,비활성화
void SkillObject::SetActive(bool flag)
{
	GameObject::SetActive(flag);

	if (flag)
	{
		// 시전자를 기준으로 시작좌표 설정
		startPos = caster.GetRealPos() + Offset;
		SetRealPos(startPos);
		auto render = GetRenderPos();
	}
	else
	{
		// 현재 애니메이션 인덱스 0으로 설정
		GetComponent<Animator>()->ResetAnimationIndex();
	}
}