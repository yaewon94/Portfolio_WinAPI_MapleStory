#include "PCH.h"
#include "Player.h"
#include "ActiveSkill.h"
#include "Animation.h"
#include "Animator.h"
#include "AssetManager.h"
#include "AttackActiveSkill.h"
#include "AttackState.h"
#include "Collider.h"
#include "FSM.h"
#include "JumpState.h"
#include "PlayerIdleState.h"
#include "Rigidbody.h"
#include "SkillManager.h"
#include "SkillObject.h"
#include "WalkState.h"

// ������
Player::Player(const wstring& name, Vec2<float> pos, Vec2<int> scale) 
	: AliveObject(name, pos, scale, LAYER_TYPE::PLAYER)
{
}

// ���� ������
Player::Player(const Player& origin) : AliveObject(origin)
{
}

// �Ҹ���
Player::~Player()
{
	for (auto& pair : skillKeyMap)
	{
		// Skill*�� ����Ű�� ��ü�� SkillManager�� ����
		pair.second = nullptr;
	}
}

// �ʱ�ȭ
void Player::Init()
{
	// ������Ʈ �߰�
	AddComponent<Rigidbody>();
	Collider* collider = AddComponent<Collider>();
	collider->SetOffset(Vec2(90.f, 80.f));
	collider->SetScale(Vec2(50, 70));
	FSM* fsm = AddComponent<FSM>();
	fsm->AddState(*new PlayerIdleState);
	fsm->AddState(*new WalkState);
	fsm->AddState(*new JumpState);
	fsm->AddState(*new AttackState);
	Animator* animator = AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::IDLE, AssetManager::GetInstance().LoadTexture(L"PlayerIdle", L"Player_Idle.png"), 3);
	animator->AddAnimation(OBJECT_STATE::WALK, AssetManager::GetInstance().LoadTexture(L"PlayerWalk", L"Player_Walk.png"), 4);
	animator->AddAnimation(OBJECT_STATE::JUMP, AssetManager::GetInstance().LoadTexture(L"PlayerJump", L"Player_Jump.png"), 1);
	animator->AddAnimation(OBJECT_STATE::ATTACK, AssetManager::GetInstance().LoadTexture(L"PlayerAttack", L"Player_AttackSwing.png"), 3, false);

	// [CHECK]
	// ��ų �߰� (�ӽ� �ϵ��ڵ�. �ð��Ǹ� DB���� �ҷ������� ���� ����)
	// �Է� Ű - ��ų ���� (�ӽ� �ϵ��ڵ�. �ð��Ǹ� DB���� �ҷ������� ���� ����)
	ActiveSkill* activeSkill = (ActiveSkill*)&AddSkill(SkillManager::GetInstance().GetSkill(0));
	AddSkillKeyMap(KEY_CODE::SHIFT, *activeSkill);

	// �ڽ� ������Ʈ �߰�
	SkillObject* skillObject = (SkillObject*)AddChild(SkillObject(L"", Vec2<float>(scale.x, scale.y * 0.5f), Vec2(20, 20), LAYER_TYPE::PLAYER_SKILL));
	((AttackActiveSkill*)activeSkill)->SetSkillObject(*skillObject);

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

	if (canJump) GetComponent<FSM>()->ChangeState(OBJECT_STATE::WALK);
	Move();
}

// [event] OnKeyDown
void Player::OnKeyDown(KEY_CODE key)
{
	if (key == KEY_CODE::LEFT || key == KEY_CODE::RIGHT)
	{
		if (canJump) GetComponent<FSM>()->ChangeState(OBJECT_STATE::WALK);
		Move();
	}
}

// [event] OnKeyReleased 
void Player::OnKeyReleased(KEY_CODE key)
{
	if (key == KEY_CODE::LEFT || key == KEY_CODE::RIGHT)
	{
		GetComponent<FSM>()->ChangeState(OBJECT_STATE::IDLE);
	}
}

// �Է� Ű - ��ų �ߵ� pair �߰�
void Player::AddSkillKeyMap(KEY_CODE keyCode, ActiveSkill& skill)
{
	auto pair = skillKeyMap.find(keyCode);

	if (pair != skillKeyMap.end()) pair->second = &skill;
	else skillKeyMap.insert(make_pair(keyCode, &skill));
}