#include "PCH.h"
#include "SkillObject.h"
#include "AttackSkillModule.h"
#include "Collider.h"
#include "TimeManager.h"

// ������
// [CHECK] ���⼭ ��� �ʱ�ȭ�ϴµ� �� ����� ���� �ȵ�? Entity������ �� �Ǵ���
SkillObject::SkillObject(const wstring& name, Vec2<float> offset, Vec2<int> scale, LAYER_TYPE layer)
	: GameObject(name, offset, scale, layer, false), skill(nullptr)
{
	if (layer == LAYER_TYPE::PLAYER_SKILL || layer == LAYER_TYPE::ENEMY_SKILL) {}
	else throw std::invalid_argument("invalid layer type");	// ��ü ���� ���
}

// ���� ������
SkillObject::SkillObject(const SkillObject& origin) : GameObject(origin), skill(origin.skill)
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

// �浹 ����
void SkillObject::OnCollisionEnter(GameObject& other)
{
	if (other.GetLayer() == LAYER_TYPE::ENEMY) SetActive(false);
}