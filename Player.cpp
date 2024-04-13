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

// 생성자
Player::Player(const wstring& name, Vec2<float> pos, Vec2<int> scale) 
	: AliveObject(name, pos, scale, LAYER_TYPE::PLAYER)
{
}

// 복사 생성자
Player::Player(const Player& origin) : AliveObject(origin)
{
}

// 소멸자
Player::~Player()
{
	for (auto& pair : skillKeyMap)
	{
		// Skill*이 가리키는 객체는 SkillManager가 지움
		pair.second = nullptr;
	}
}

// 초기화
void Player::Init()
{
	// 컴포넌트 추가
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
	// 스킬 추가 (임시 하드코딩. 시간되면 DB에서 불러오도록 구현 예정)
	// 입력 키 - 스킬 설정 (임시 하드코딩. 시간되면 DB에서 불러오도록 구현 예정)
	ActiveSkill* activeSkill = (ActiveSkill*)&AddSkill(SkillManager::GetInstance().GetSkill(0));
	AddSkillKeyMap(KEY_CODE::SHIFT, *activeSkill);

	// 자식 오브젝트 추가
	SkillObject* skillObject = (SkillObject*)AddChild(SkillObject(L"", Vec2<float>(scale.x, scale.y * 0.5f), Vec2(20, 20), LAYER_TYPE::PLAYER_SKILL));
	((AttackActiveSkill*)activeSkill)->SetSkillObject(*skillObject);

	// 필드 초기화
	SetSkillObject(*(SkillObject*)GetChild(LAYER_TYPE::PLAYER_SKILL));

	// 최상위 부모 Init() 호출
	GameObject::Init();
}

// [event] OnKeyPressed
void Player::OnKeyPressed(KEY_CODE key)
{
	// [check] 키세팅 커스터마이징 할 때는 자기가 셋팅한 키값대로 분기시켜야 함
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

// 입력 키 - 스킬 발동 pair 추가
void Player::AddSkillKeyMap(KEY_CODE keyCode, ActiveSkill& skill)
{
	auto pair = skillKeyMap.find(keyCode);

	if (pair != skillKeyMap.end()) pair->second = &skill;
	else skillKeyMap.insert(make_pair(keyCode, &skill));
}