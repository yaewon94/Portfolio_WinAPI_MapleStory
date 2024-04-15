#include "PCH.h"
#include "SkillObject.h"
#include "AttackActiveSkill.h"
#include "Collider.h"
#include "TimeManager.h"

// 생성자
// [CHECK] 여기서 상수 초기화하는데 왜 제대로 적용 안됨? Entity에서는 잘 되던데
SkillObject::SkillObject(const wstring& name, Vec2 offset, Vec2 scale, LAYER_TYPE layer)
	: GameObject(name, offset, scale, layer, false), skill(nullptr)
{
	if (layer == LAYER_TYPE::PLAYER_SKILL) {}
	else throw std::invalid_argument("invalid layer type");	// 객체 생성 취소
}

// 복사 생성자
SkillObject::SkillObject(const SkillObject& origin) : GameObject(origin), skill(origin.skill)
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
}

// 매 프레임마다 호출
void SkillObject::Tick()
{
	// 최대 이동거리를 넘어서면 자동으로 비활성화
	if (offset - StartPos > skill->GetMaxRange())
	{
		SetActive(false);
		return;
	}

	offset += skill->GetMaxRange() * skill->GetSpeed() * TimeManager::GetInstance().GetDeltaTime();
}

// 충돌 시작
void SkillObject::OnCollisionEnter(GameObject& other)
{
	if (other.GetLayer() == LAYER_TYPE::ENEMY) SetActive(false);
}