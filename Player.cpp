#include "PCH.h"
#include "Player.h"
#include "ActiveSkill.h"
#include "Animation.h"
#include "Animator.h"
#include "AssetManager.h"
#include "Collider.h"
#include "FSM.h"
#include "LevelManager.h"
#include "MapManager.h"
#include "PlayerAttackSkill.h"
#include "Rigidbody.h"
#include "SkillManager.h"
#include "SkillObject.h"

// ������
Player::Player(const wstring& name, int MaxHP)
	: AliveObject(name, LAYER_TYPE::PLAYER, MaxHP), currentMap(nullptr)
{
}

// ���� ������
Player::Player(const Player& origin) : AliveObject(origin), currentMap(origin.currentMap)
{
}

// �Ҹ���
Player::~Player()
{
	currentMap = nullptr;

	for (auto& pair : skillKeyMap)
	{
		// Skill*�� ����Ű�� ��ü�� SkillManager�� ����
		pair.second = nullptr;
	}
}

// Ư����ų ��� �� �ڽ�Ʈ �Ҹ�
void Player::UseSkillCost(int cost)
{
	currentSkillCost -= cost;
	LevelManager::GetInstance().OnChangeGaugePercent(currentSkillCost);
}

// ��ų �ڽ�Ʈ ȸ��
void Player::FillSkillCost(int cost)
{
	currentSkillCost += cost;
	LevelManager::GetInstance().OnChangeGaugePercent(currentSkillCost);
}

// �� ����
void Player::ChangeMap(Map& map)
{
	MapManager::GetInstance().ChangeMap(currentMap, &map);
	currentMap = &map;
}

// �ʱ�ȭ
void Player::Init()
{
	// ������Ʈ �߰�
	AddComponent<Rigidbody>();
	Collider* collider = AddComponent<Collider>();
	collider->SetScale(Vec2(50, 70));
	FSM* fsm = AddComponent<FSM>();
	fsm->SetDefaultState(OBJECT_STATE::IDLE);
	Animator* animator = AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::IDLE, AssetManager::GetInstance().LoadTexture(L"PlayerIdle", L"Player_Idle.png"), 3);
	animator->AddAnimation(OBJECT_STATE::WALK, AssetManager::GetInstance().LoadTexture(L"PlayerWalk", L"Player_Walk.png"), 4);
	animator->AddAnimation(OBJECT_STATE::JUMP, AssetManager::GetInstance().LoadTexture(L"PlayerJump", L"Player_Jump.png"), 1);
	animator->AddAnimation(OBJECT_STATE::ATTACK, AssetManager::GetInstance().LoadTexture(L"PlayerAttack", L"Player_AttackSwing.png"), 3, false);

	// [CHECK]
	// ��ų �߰� (�ӽ� �ϵ��ڵ�. �ð��Ǹ� DB���� �ҷ������� ���� ����)
	// �Է� Ű - ��ų ���� (�ӽ� �ϵ��ڵ�. �ð��Ǹ� DB���� �ҷ������� ���� ����)
	ActiveSkill::SetPlayer(this);
	ActiveSkill* activeSkill = (ActiveSkill*)&AddSkill(SkillManager::GetInstance().GetSkill(0));
	AddSkillKeyMap(KEY_CODE::SHIFT, *activeSkill);

	// �ڽ� ������Ʈ �߰�
	SkillObject* skillObject = (SkillObject*)AddChild(SkillObject(L"", Vec2<float>((float)scale.x, 0.f), Vec2(20, 20), LAYER_TYPE::PLAYER_SKILL));

	// �ʵ� �ʱ�ȭ
	SetSkillObject(*(SkillObject*)GetChild(LAYER_TYPE::PLAYER_SKILL));

	// �ֻ��� �θ� Init() ȣ��
	GameObject::Init();
}

// [event] OnKeyPressed
void Player::OnKeyPressed(KEY_CODE key)
{
	// [check] Ű���� Ŀ���͸���¡ �� ���� �ڱⰡ ������ Ű����� �б���Ѿ� ��
	switch (key)
	{
	case KEY_CODE::X:
		Jump();
		return;
	case KEY_CODE::LEFT:
		dir = Vec2<float>::Left();
		break;
	case KEY_CODE::RIGHT:
		dir = Vec2<float>::Right();
		break;
	default:
		return;
	}

	Move();
}

// [event] OnKeyDown
void Player::OnKeyDown(KEY_CODE key)
{
	if (key == KEY_CODE::LEFT || key == KEY_CODE::RIGHT) Move();
}

// [event] OnKeyReleased 
void Player::OnKeyReleased(KEY_CODE key)
{
	if (key == KEY_CODE::LEFT || key == KEY_CODE::RIGHT)
	{
		FSM* fsm = GetComponent<FSM>();
		fsm->ChangeState(fsm->GetDefaultState());
	}
}

// [event] �浹 ����
void Player::OnCollisionEnter(GameObject& other)
{
	AliveObject::OnCollisionEnter(other);

	// ���� �浹
	if (other.GetLayer() == LAYER_TYPE::GROUND)
	{
		if (!canJump)
		{
			FSM* fsm = GetComponent<FSM>();
			if (fsm->GetCurrentState() != OBJECT_STATE::ATTACK) fsm->ChangeState(fsm->GetDefaultState());
			GetComponent<Rigidbody>()->UseGravity(false);
			canJump = true;
		}
	}
	// ���� ��ų�� �¾��� ���
	if (other.GetLayer() == LAYER_TYPE::ENEMY_SKILL)
	{
		// ���� ü���� 0 �̻��϶���
		if (GetCurrentHP() > 0)
		{
			// ���� ��������ŭ ü�� ���ҽ�Ŵ
			SkillObject * obj = (SkillObject*)&other;
			int damage = (int)(obj->GetSkill()->GetCoefficient() * GetMaxHP());	// �÷��̾� �ִ�ü�� ��� ������
			OnChangeHP(-damage);

			// ü���� 0�� ��� Dead ���·� ��ȯ
			//if (GetCurrentHP() == 0) GetComponent<FSM>()->ChangeState(OBJECT_STATE::DEAD_BEFORE);
		}
	}
}

// �Է� Ű - ��ų �ߵ� pair �߰�
void Player::AddSkillKeyMap(KEY_CODE keyCode, ActiveSkill& skill)
{
	auto pair = skillKeyMap.find(keyCode);

	if (pair != skillKeyMap.end()) pair->second = &skill;
	else skillKeyMap.insert(make_pair(keyCode, &skill));
}