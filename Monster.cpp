#include "PCH.h"
#include "Monster.h"
#include "Collider.h"
#include "DeadBeforeState.h"
#include "EnemyAttackSkill.h"
#include "FSM.h"
#include "LevelManager.h"
#include "MonsterAttackState.h"
#include "MonsterDeadState.h"
#include "MonsterIdleState.h"
#include "MonsterTraceState.h"
#include "Player.h"
#include "PlayerAttackSkill.h"
#include "RandomManager.h"
#include "Skill.h"
#include "SkillObject.h"

// static �ʵ� �ʱ�ȭ
Player* Monster::player = nullptr;

// ������
Monster::Monster(const wstring& name, int MaxHP)
	: AliveObject(name, LAYER_TYPE::ENEMY, MaxHP)
{
}

// ���� ������
Monster::Monster(const Monster& origin) 
	: AliveObject(origin)
	, detectRange(origin.detectRange)
{
}

// �Ҹ���
Monster::~Monster()
{
}

// �ʱ�ȭ
void Monster::Init()
{
	// �ʵ� �ʱ�ȭ
	if (player == nullptr) player = static_cast<Player*>(LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER));

	// ������Ʈ �߰�
	// �Ϻ� ������Ʈ�� ���� ������ Enter()���� �߰���
	Collider* collider = AddComponent<Collider>();
	//collider->SetScale(DEFAULT_OBJECT_SCALE);
	FSM* fsm = AddComponent<FSM>();
	fsm->SetDefaultState(OBJECT_STATE::IDLE);
	fsm->AddState(*new MonsterIdleState);
	fsm->AddState(*new MonsterTraceState);
	fsm->AddState(*new MonsterAttackState(3.f));
	fsm->AddState(*new DeadBeforeState(3.f));
	fsm->AddState(*new MonsterDeadState(5.f));

	// TODO : ���� ��ų DB
	// ���͸��� ������ų�� �ٸ��Ƿ� �ӽ÷� �������� �߰�������

	// �ڽ� ������Ʈ �߰�
	SkillObject* skillObject = (SkillObject*)AddChild(SkillObject(L"", Vec2(150.f, 0.f), DEFAULT_OBJECT_SCALE, LAYER_TYPE::ENEMY_SKILL));

	// �ʵ� �ʱ�ȭ
	SetSkillObject(*(SkillObject*)GetChild(LAYER_TYPE::ENEMY_SKILL));

	// �ֻ��� �θ� Init() ȣ��
	GameObject::Init();
}

// �浹 ����
void Monster::OnCollisionEnter(GameObject& other)
{
	AliveObject::OnCollisionEnter(other);

	// �÷��̾� ��ų�� �¾��� ���
	if (other.GetLayer() == LAYER_TYPE::PLAYER_SKILL)
	{
		// ���� ü���� 0 �̻��϶���
		if (GetCurrentHP() > 0)
		{
			// ���� ��������ŭ ü�� ���ҽ�Ŵ
			SkillObject* obj = (SkillObject*)&other;
			int damage = (int)(obj->GetSkill()->GetCoefficient() * player->GetPower());
			OnChangeHP(-damage);

			// TODO : �Ϲݸ��� Ŭ������ �������� Ŭ������ �и��ؼ� �����ؾ� ��
			// ü���� 0�� ��� �������� ü�� 0 �˸� ȣ��
			if (GetCurrentHP() == 0) LevelManager::GetInstance().OnAlertBossHPzero();
		}
	}
}

// �浹 ��
void Monster::OnCollisionStay(GameObject& other)
{
}

// �浹 ����
void Monster::OnCollisionExit(GameObject& other)
{
}

// ����
void Monster::Attack()
{
	// ���Ͱ� ������ �ִ� ��ų���� �������� ���
	int index = RandomManager::Create(GetSkillCount());

	Skill* skill = &GetSkill(index);
	skill->UseSkill(this, (SkillObject*)GetChild(LAYER_TYPE::ENEMY_SKILL));
}

// �÷��̾� ����
bool Monster::DetectPlayer()
{
	static float playerRad = sqrtf(0.25f * (player->GetScale().x * player->GetScale().x + player->GetScale().y * player->GetScale().y));

	if (GetRealPos().GetDistance(player->GetRealPos()) <= detectRange + playerRad) return true;
	else return false;
}

// �÷��̾� �߰�
// @ return : �÷��̾� ��ó�� �����ߴ��� ����
bool Monster::Trace()
{
	// ���� �Ÿ� �̳������� �߰�
	if (GetRealPos().GetDistance(player->GetRealPos()) <= MAX_TRACE_DISTANCE)
	{
		return true;
	}
	else
	{
		// ���� ����
		if (GetRealPos().x - player->GetRealPos().x > 0) dir = Vec2<float>::Left();
		else dir = Vec2<float>::Right();

		// �̵�
		Move();

		return false;
	}
}