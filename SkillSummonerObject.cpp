#include "PCH.h"
#include "SkillSummonerObject.h"
#include "EnemyAttackSkill.h"
#include "SkillManager.h"
#include "SkillObject.h"

// ������
SkillSummonerObject::SkillSummonerObject(const wstring& name, LAYER_TYPE layer, int objCount, EnemyAttackSkill& skill) 
	: GameObject(name, DEFAULT_OBJECT_POS, DEFAULT_OBJECT_SCALE, layer)
	, ObjCount(objCount), skill(&skill)
{
	skillVelocityVec.resize(ObjCount);
}

// ���� ������
SkillSummonerObject::SkillSummonerObject(const SkillSummonerObject& origin) 
	: GameObject(origin)
	, ObjCount(origin.ObjCount), skill(origin.skill), skillVelocityVec(origin.skillVelocityVec)
{
}

// �Ҹ���
SkillSummonerObject::~SkillSummonerObject()
{
	for (auto obj : skillObjects)
	{
		// �������� ������Ʈ ������ �� �ڽĿ�����Ʈ(��ų������Ʈ��) ���� ������
		obj = nullptr;
	}

	skill = nullptr;
}

// �ʱ�ȭ
void SkillSummonerObject::Init()
{
	// ����� ��ų ������Ʈ �߰�
	for (int i=0; i<skillVelocityVec.size(); ++i)
	{
		skillObjects.push_back(new SkillObject(name, *this, DEFAULT_OBJECT_POS, DEFAULT_OBJECT_SCALE, LAYER_TYPE::ENEMY_SKILL));
		auto obj = skillObjects.back();
		obj->SetParent(*this);
		obj->AddSkill(skill->GetIndex());
		obj->SetSkill(skill, skill, skillVelocityVec[i]);
	}

	// �ֻ��� �θ� Init() ȣ��
	GameObject::Init();
}

// ��ų ��ȯ(���)
void SkillSummonerObject::UseSkill()
{
	GameObject::SetActive(true);

	for (auto skillObj : skillObjects)
	{
		// ������ �ð� ���Ŀ� ��ų������Ʈ Ȱ��ȭ �ǵ��� ����
		SkillManager::GetInstance().LaunchSkill(skill, skillObj);
	}
}