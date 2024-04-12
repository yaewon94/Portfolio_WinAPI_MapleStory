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

// 생성자
Player::Player(const wstring& name, Vec2 pos, Vec2 scale) : AliveObject(name, pos, scale, LAYER_TYPE::PLAYER)
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
		if (pair.second != nullptr) pair.second = nullptr;
	}
}

// 초기화
void Player::Init()
{
	// 컴포넌트 추가
	AddComponent<Rigidbody>();
	AddComponent<Collider>();
	FSM* fsm = AddComponent<FSM>();
	fsm->AddState(*new PlayerIdleState);
	Animator* animator = AddComponent<Animator>();
	animator->AddAnimation(OBJECT_STATE::IDLE, AssetManager::GetInstance().LoadTexture(L"PlayerIdle", L"Player_Idle.png"), 3);

	// 자식 오브젝트 추가
	SkillObject* skillObject = (SkillObject*)AddChild(SkillObject(L"", Vec2(scale.x, scale.y * 0.5f), Vec2(20, 20), LAYER_TYPE::PLAYER_SKILL));
	AttackActiveSkill::SetSkillObject(*skillObject);

	// 필드 초기화
	SetSkillObject(*(SkillObject*)GetChild(LAYER_TYPE::PLAYER_SKILL));

	// [CHECK]
	// 스킬 추가 (임시 하드코딩. 시간되면 DB에서 불러오도록 구현 예정)
	// 입력 키 - 스킬 설정 (임시 하드코딩. 시간되면 DB에서 불러오도록 구현 예정)
	ActiveSkill* activeSkill = (ActiveSkill*)&AddSkill(SkillManager::GetInstance().GetSkill(0));
	AddSkillKeyMap(KEY_CODE::SHIFT, *activeSkill);

	// 최상위 부모 Init() 호출
	GameObject::Init();
}

// 이번 프레임에 처음 눌렸을 때 호출
void Player::OnKeyPressed(KEY_CODE key)
{
	// [check] 키세팅 커스터마이징 할 때는 자기가 셋팅한 키값대로 분기시켜야 함
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

// 저번 프레임에도 눌리고, 이번 프레임에도 눌렸을 때 호출
void Player::OnKeyDown(KEY_CODE key)
{
	if (key == KEY_CODE::LEFT || key == KEY_CODE::RIGHT) Move();
}

// 입력 키 - 스킬 발동 pair 추가
void Player::AddSkillKeyMap(KEY_CODE keyCode, ActiveSkill& skill)
{
	auto pair = skillKeyMap.find(keyCode);

	if (pair != skillKeyMap.end()) pair->second = &skill;
	else skillKeyMap.insert(make_pair(keyCode, &skill));
}