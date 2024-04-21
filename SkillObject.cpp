#include "PCH.h"
#include "SkillObject.h"
#include "AttackSkillModule.h"
#include "Collider.h"
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
}

// 초기화
void SkillObject::Init()
{
	AddComponent<Collider>();

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

// 스킬오브젝트 활성화,비활성화
void SkillObject::SetActive(bool flag)
{
	GameObject::SetActive(flag);

	if (flag)
	{
		// 시전자를 기준으로 시작좌표 설정
		startPos = caster.GetRealPos() + Offset;
		SetRealPos(startPos);
	}
}