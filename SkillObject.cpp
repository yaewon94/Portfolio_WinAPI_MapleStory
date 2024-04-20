#include "PCH.h"
#include "SkillObject.h"
#include "AttackSkillModule.h"
#include "Collider.h"
#include "TimeManager.h"

// 생성자
// [CHECK] 여기서 상수 초기화하는데 왜 제대로 적용 안됨? Entity에서는 잘 되던데
SkillObject::SkillObject(const wstring& name, Vec2<float> offset, Vec2<int> scale, LAYER_TYPE layer)
	: GameObject(name, offset, scale, layer, false), skill(nullptr)
{
	if (layer == LAYER_TYPE::PLAYER_SKILL || layer == LAYER_TYPE::ENEMY_SKILL) {}
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
	if (time >= skill->GetDuration()
		|| offset - StartPos > skill->GetMaxRange())
	{
		offset = StartPos;
		time = 0.f;
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