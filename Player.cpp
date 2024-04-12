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
	AddComponent<Collider>();
	FSM* fsm = AddComponent<FSM>();
	fsm->AddState(*new PlayerIdleState);
	Animator* animator = AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::IDLE, AssetManager::GetInstance().LoadTexture(L"PlayerIdle", L"Player_Idle.png"), 3);

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

// �̹� �����ӿ� ó�� ������ �� ȣ��
void Player::OnKeyPressed(KEY_CODE key)
{
	// [check] Ű���� Ŀ���͸���¡ �� ���� �ڱⰡ ������ Ű����� �б���Ѿ� ��
	switch (key)
	{
	case KEY_CODE::X:
		Jump();
		break;
	case KEY_CODE::LEFT:
		dir = Vec2::Left();
		Move();
		break;
	case KEY_CODE::RIGHT:
		dir = Vec2::Right();
		Move();
		break;
	}
}

// ���� �����ӿ��� ������, �̹� �����ӿ��� ������ �� ȣ��
void Player::OnKeyDown(KEY_CODE key)
{
	if (key == KEY_CODE::LEFT || key == KEY_CODE::RIGHT) Move();
}

// �Է� Ű - ��ų �ߵ� pair �߰�
void Player::AddSkillKeyMap(KEY_CODE keyCode, ActiveSkill& skill)
{
	auto pair = skillKeyMap.find(keyCode);

	if (pair != skillKeyMap.end()) pair->second = &skill;
	else skillKeyMap.insert(make_pair(keyCode, &skill));
}