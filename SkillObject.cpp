#include "PCH.h"
#include "SkillObject.h"
#include "AttackSkillModule.h"
#include "Collider.h"
#include "TimeManager.h"

// ������
SkillObject::SkillObject(const wstring& name, GameObject& caster, Vec2<float> offset, Vec2<int> scale, LAYER_TYPE layer)
	: GameObject(name, offset, scale, layer, false)
	, caster(caster), Offset(offset), skill(nullptr)
{
	if (layer == LAYER_TYPE::PLAYER_SKILL || layer == LAYER_TYPE::ENEMY_SKILL) {}
	else throw std::invalid_argument("invalid layer type");	// ��ü ���� ���
}

// ���� ������
SkillObject::SkillObject(const SkillObject& origin) 
	: GameObject(origin)
	, caster(origin.caster), Offset(origin.offset), skill(origin.skill)
{
}

// �Ҹ���
SkillObject::~SkillObject()
{
	skill = nullptr;
}

// �ʱ�ȭ
void SkillObject::Init()
{
	AddComponent<Collider>();

	// �ֻ��� �θ� Init() ȣ��
	GameObject::Init();
}

// �� �����Ӹ��� ȣ��
void SkillObject::Tick()
{
	float dt = TimeManager::GetInstance().GetDeltaTime();
	time += dt;

	// ��ų������Ʈ Ȱ��ȭ �ð��� �����ų�
	// �ִ� �̵��Ÿ��� �Ѿ�� �ڵ����� ��Ȱ��ȭ
	// �Ǵ� ���濡�� �¾��� �� ��Ȱ��ȭ (�̰� �ܺο��� ó����)
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

// �浹 ����
void SkillObject::OnCollisionEnter(GameObject& other)
{
	if (other.GetLayer() == LAYER_TYPE::ENEMY) SetActive(false);
}

// ��ų������Ʈ Ȱ��ȭ,��Ȱ��ȭ
void SkillObject::SetActive(bool flag)
{
	GameObject::SetActive(flag);

	if (flag)
	{
		// �����ڸ� �������� ������ǥ ����
		startPos = caster.GetRealPos() + Offset;
		SetRealPos(startPos);
	}
}