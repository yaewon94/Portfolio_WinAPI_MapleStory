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
	, caster(caster), Offset(offset)
	, attackSkillPtr(nullptr), skillPtr(nullptr)
{
	if (layer == LAYER_TYPE::PLAYER_SKILL || layer == LAYER_TYPE::ENEMY_SKILL) {}
	else throw std::invalid_argument("invalid layer type");	// ��ü ���� ���
}

// ���� ������
// ERROR : caster �����ϴµ� �����־ ����ȉ�
SkillObject::SkillObject(const SkillObject& origin) 
	: GameObject(origin)
	//, caster(nullptr) //, caster(origin.caster)
	, caster(origin.caster)
	, Offset(origin.offset), velocity(origin.velocity), startPos(origin.startPos)
	, attackSkillPtr(origin.attackSkillPtr), skillPtr(origin.skillPtr)
{
}

// �Ҹ���
SkillObject::~SkillObject()
{
	attackSkillPtr = nullptr;
	skillPtr = nullptr;

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

	// ��ų �ִϸ��̼� ����
	if (skillPtr != nullptr)
	{
		auto iter = skillMap.find(skillPtr->GetIndex());
		auto& pair = skillMap.find(skillPtr->GetIndex())->second;
		if (pair.size() > 0) GetComponent<Animator>()->SetAnimationMap(pair, skillPtr->GetObjectState());
	}

	// �ֻ��� �θ� Init() ȣ��
	GameObject::Init();
}

// �� �����Ӹ��� ȣ��
void SkillObject::Tick()
{
	float dt = TimeManager::GetInstance().GetDeltaTime();
	time += dt;

	// ��ų������Ʈ Ȱ��ȭ �ð��� ������ ��Ȱ��ȭ
	if (time >= attackSkillPtr->GetDuration())
	{
		time = 0.f;
		SetActive(false);
		return;
	}
	// �ִ� �̵��Ÿ��� �Ѿ�� ���
	if (GetRealPos() - startPos > velocity)
	{
		// ���ӽð� ������ ���� ���� ��� ��Ȱ��ȭ
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
	// �Ǵ� ���濡�� �¾��� �� ��Ȱ��ȭ (�̰� �ܺο��� ó����)

	// ������ ���ǿ� �ش����� ������ ��ų������Ʈ �̵�
	Vec2<float> curPos = GetRealPos() + velocity * attackSkillPtr->GetSpeed() * TimeManager::GetInstance().GetDeltaTime();
	SetRealPos(curPos);
}

// �浹 ����
void SkillObject::OnCollisionEnter(GameObject& other)
{
	//if (other.GetLayer() == LAYER_TYPE::ENEMY) SetActive(false);
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

	// ��ų �ִϸ��̼� ����
	if (pair.size() > 0) GetComponent<Animator>()->SetAnimationMap(pair, me_skill->GetObjectState());
}

// ��ų������Ʈ Ȱ��ȭ,��Ȱ��ȭ
void SkillObject::SetActive(bool flag)
{
	GameObject::SetActive(flag);

	if (flag)
	{
		// ���� �ִϸ��̼� �ε��� 0���� ����
		GetComponent<Animator>()->ResetAnimationIndex();

		// �����ڸ� �������� ������ǥ ����
		startPos = caster.GetRealPos() + Offset;
		SetRealPos(startPos);
	}
	else
	{
		// ���� �ִϸ��̼� �ε��� 0���� ����
		//GetComponent<Animator>()->ResetAnimationIndex();

		// �ݹ��Լ��� ������ ȣ��
		if (skillPtr != nullptr) skillPtr->OnDisappear(this);
	}
}
