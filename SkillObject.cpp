#include "PCH.h"
#include "SkillObject.h"
#include "Animation.h"
#include "Animator.h"
#include "AttackSkillModule.h"
#include "Collider.h"
#include "Skill.h"
#include "SkillManager.h"
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

	// �ִϸ����Ϳ� �ִ� �ִϸ��̼� �ʱ�ȭ
	GetComponent<Animator>()->ClearAnimationMap();

	// ��ų �ִϸ��̼� ����
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

// �ʱ�ȭ
void SkillObject::Init()
{
	// ������Ʈ �߰�
	AddComponent<Collider>();
	AddComponent<Animator>();

	// ��� ��ų�� ���� �ʱ�ȭ
	for (auto& skillPair : skillMap)
	{
		// ��ų �ִϸ��̼� map ����
		Skill& skill = SkillManager::GetInstance().GetSkill(skillPair.first);
		for (auto& state_anim_pair : skill.GetAnimationMap())
		{
			skillPair.second.insert(make_pair(state_anim_pair.first, state_anim_pair.second->Clone()));
		}
	}

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

// ��ų������Ʈ�� ����ϴ� ��ų�� �߰�
void SkillObject::AddSkill(int index)
{
	map<OBJECT_STATE, Animation*> map;
	skillMap.insert(make_pair(index, map));
}

// ���� ����� ��ų ����
void SkillObject::SetSkill(AttackSkillModule* me_attack, Skill* me_skill)
{
	if (this->skill == me_attack) return;

	this->skill = me_attack;
	auto& pair = skillMap.find(me_skill->GetIndex())->second;

	// ��ų �ִϸ��̼� ����
	if(pair.size() > 0) GetComponent<Animator>()->SetAnimationMap(pair, me_skill->GetObjectState());
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
		auto render = GetRenderPos();
	}
	else
	{
		// ���� �ִϸ��̼� �ε��� 0���� ����
		GetComponent<Animator>()->ResetAnimationIndex();
	}
}