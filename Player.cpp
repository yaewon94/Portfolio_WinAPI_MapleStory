#include "PCH.h"
#include "Player.h"
#include "ActiveSkill.h"
#include "Animation.h"
#include "Animator.h"
#include "AssetManager.h"
#include "AttackActiveSkill.h"
#include "Collider.h"
#include "FSM.h"
#include "PlayerIdleState.h"
#include "Rigidbody.h"
#include "SkillManager.h"
#include "SkillObject.h"
#include "WalkState.h"

// ������
Player::Player(const wstring& name, Vec2 pos, Vec2 scale) : AliveObject(name, pos, scale, LAYER_TYPE::PLAYER)
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
		if (pair.second != nullptr) pair.second = nullptr;
	}
}

// �ʱ�ȭ
void Player::Init()
{
	// ������Ʈ �߰�
	AddComponent<Rigidbody>();
	Collider* collider = AddComponent<Collider>();
	collider->SetOffset(Vec2(90, 80));
	collider->SetScale(Vec2(50, 70));
	FSM* fsm = AddComponent<FSM>();
	fsm->AddState(*new PlayerIdleState);
	fsm->AddState(*new WalkState);
	Animator* animator = AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::IDLE, AssetManager::GetInstance().LoadTexture(L"PlayerIdle", L"Player_Idle.png"), 3);
	animator->AddAnimation(OBJECT_STATE::WALK, AssetManager::GetInstance().LoadTexture(L"PlayerWalk", L"Player_Walk.png"), 4);

	// �ڽ� ������Ʈ �߰�
	SkillObject* skillObject = (SkillObject*)AddChild(SkillObject(L"", Vec2(scale.x, scale.y * 0.5f), Vec2(20, 20), LAYER_TYPE::PLAYER_SKILL));
	AttackActiveSkill::SetSkillObject(*skillObject);

	// �ʵ� �ʱ�ȭ
	SetSkillObject(*(SkillObject*)GetChild(LAYER_TYPE::PLAYER_SKILL));

	// [CHECK]
	// ��ų �߰� (�ӽ� �ϵ��ڵ�. �ð��Ǹ� DB���� �ҷ������� ���� ����)
	// �Է� Ű - ��ų ���� (�ӽ� �ϵ��ڵ�. �ð��Ǹ� DB���� �ҷ������� ���� ����)
	ActiveSkill* activeSkill = (ActiveSkill*)&AddSkill(SkillManager::GetInstance().GetSkill(0));
	AddSkillKeyMap(KEY_CODE::SHIFT, *activeSkill);

	// �ֻ��� �θ� Init() ȣ��
	GameObject::Init();
}

// �� �����Ӹ��� ȣ��
void Player::FinalTick()
{
	// ���� üũ
	FSM* fsm = GetComponent<FSM>();
	if (curState != fsm->GetCurrentState()) fsm->ChangeState(curState);

	// �ֻ��� �θ� FinalTick() ȣ��
	GameObject::FinalTick();
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
		dir = Vec2::Left();
		//curState = OBJECT_STATE::WALK;
		//Move();
		break;
	case KEY_CODE::RIGHT:
		dir = Vec2::Right();
		//curState = OBJECT_STATE::WALK;
		//Move();
		break;
	default:
		return;
	}

	curState = OBJECT_STATE::WALK;
	Move();
}

// [event] OnKeyDown
void Player::OnKeyDown(KEY_CODE key)
{
	if (key == KEY_CODE::LEFT || key == KEY_CODE::RIGHT)
	{
		curState = OBJECT_STATE::WALK;
		Move();
	}
}

// [event] OnKeyReleased 
void Player::OnKeyReleased(KEY_CODE key)
{
	if (key == KEY_CODE::LEFT || key == KEY_CODE::RIGHT) curState = OBJECT_STATE::IDLE;
}

// �Է� Ű - ��ų �ߵ� pair �߰�
void Player::AddSkillKeyMap(KEY_CODE keyCode, ActiveSkill& skill)
{
	auto pair = skillKeyMap.find(keyCode);

	if (pair != skillKeyMap.end()) pair->second = &skill;
	else skillKeyMap.insert(make_pair(keyCode, &skill));
}