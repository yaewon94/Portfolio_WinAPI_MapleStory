#include "PCH.h"
#include "SkillObject.h"
#include "AttackActiveSkill.h"
#include "Collider.h"
#include "TimeManager.h"

// static �ʵ� �ʱ�ȭ
AttackActiveSkill* SkillObject::skill = nullptr;

// ������
// [CHECK] ���⼭ ��� �ʱ�ȭ�ϴµ� �� ����� ���� �ȵ�? Entity������ �� �Ǵ���
SkillObject::SkillObject(const wstring& name, Vec2 offset, Vec2 scale, LAYER_TYPE layer)
	: GameObject(name, offset, scale, layer, false)
{
	if (layer == LAYER_TYPE::PLAYER_SKILL) {}
	else throw std::invalid_argument("invalid layer type");	// ��ü ���� ���
}

// ���� ������
SkillObject::SkillObject(const SkillObject& origin) : GameObject(origin)
{
}

// �Ҹ���
SkillObject::~SkillObject()
{
}

// �ʱ�ȭ
void SkillObject::Init()
{
	AddComponent<Collider>();
}

// �� �����Ӹ��� ȣ��
void SkillObject::Tick()
{
	// �ִ� �̵��Ÿ��� �Ѿ�� �ڵ����� ��Ȱ��ȭ
	if (offset - StartPos > skill->GetMaxRange())
	{
		SetActive(false);
		return;
	}

	offset += (skill->GetMaxRange() * skill->GetSpeed() * TimeManager::GetInstance().GetDeltaTime());
}

// �浹 ����
void SkillObject::OnCollisionEnter(GameObject& other)
{
	if (other.GetLayer() == LAYER_TYPE::ENEMY) SetActive(false);
}