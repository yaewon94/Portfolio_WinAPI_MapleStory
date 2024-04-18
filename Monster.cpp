#include "PCH.h"
#include "Monster.h"
#include "AttackActiveSkill.h"
#include "Collider.h"
#include "LevelManager.h"
#include "Player.h"
#include "SkillObject.h"

// static �ʵ� �ʱ�ȭ
Player* Monster::player = nullptr;

// ������
Monster::Monster(const wstring& name, int MaxHP)
	: AliveObject(name, LAYER_TYPE::ENEMY, MaxHP, 100.f)
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

// �÷��̾� ����
bool Monster::DetectPlayer()
{
	static float playerRad = sqrtf(0.25f * (player->GetScale().x * player->GetScale().x + player->GetScale().y * player->GetScale().y));

	if (GetRealPos().GetDistance(player->GetRealPos()) <= detectRange + playerRad) return true;
	else return false;
}

// �÷��̾� �߰�
bool Monster::Trace()
{
	// ���� �Ÿ� �̳������� �߰�
	if (GetRealPos().GetDistance(player->GetRealPos()) <= MAX_TRACE_DISTANCE)
	{
		return false;
	}
	else
	{
		// ���� ����
		if (GetRealPos().x - player->GetRealPos().x > 0) dir = Vec2<float>::Left();
		else dir = Vec2<float>::Right();

		// �̵�
		Move();

		return true;
	}
}