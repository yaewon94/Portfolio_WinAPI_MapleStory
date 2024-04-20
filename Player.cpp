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

// 생성자
Player::Player(const wstring& name, int MaxHP)
	: AliveObject(name, LAYER_TYPE::PLAYER, MaxHP), currentMap(nullptr)
{
}

// 복사 생성자
Player::Player(const Player& origin) : AliveObject(origin), currentMap(origin.currentMap)
{
}

// 소멸자
Player::~Player()
{
	currentMap = nullptr;

	for (auto& pair : skillKeyMap)
	{
		// Skill*이 가리키는 객체는 SkillManager가 지움
		pair.second = nullptr;
	}
}

// 특수스킬 사용 시 코스트 소모
void Player::UseSkillCost(int cost)
{
	currentSkillCost -= cost;
	LevelManager::GetInstance().OnChangeGaugePercent(currentSkillCost);
}

// 스킬 코스트 회복
void Player::FillSkillCost(int cost)
{
	currentSkillCost += cost;
	LevelManager::GetInstance().OnChangeGaugePercent(currentSkillCost);
}

// 맵 변경
void Player::ChangeMap(Map& map)
{
	MapManager::GetInstance().ChangeMap(currentMap, &map);
	currentMap = &map;
}

// 초기화
void Player::Init()
{
	// 컴포넌트 추가
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
	// 스킬 추가 (임시 하드코딩. 시간되면 DB에서 불러오도록 구현 예정)
	// 입력 키 - 스킬 설정 (임시 하드코딩. 시간되면 DB에서 불러오도록 구현 예정)
	ActiveSkill::SetPlayer(this);
	ActiveSkill* activeSkill = (ActiveSkill*)&AddSkill(SkillManager::GetInstance().GetSkill(0));
	AddSkillKeyMap(KEY_CODE::SHIFT, *activeSkill);

	// 자식 오브젝트 추가
	SkillObject* skillObject = (SkillObject*)AddChild(SkillObject(L"", Vec2<float>((float)scale.x, 0.f), Vec2(20, 20), LAYER_TYPE::PLAYER_SKILL));

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

// [event] 충돌 시작
void Player::OnCollisionEnter(GameObject& other)
{
	AliveObject::OnCollisionEnter(other);

	// 지면 충돌
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
	// 몬스터 스킬에 맞았을 경우
	if (other.GetLayer() == LAYER_TYPE::ENEMY_SKILL)
	{
		// 현재 체력이 0 이상일때만
		if (GetCurrentHP() > 0)
		{
			// 입은 데미지만큼 체력 감소시킴
			SkillObject * obj = (SkillObject*)&other;
			int damage = (int)(obj->GetSkill()->GetCoefficient() * GetMaxHP());	// 플레이어 최대체력 비례 데미지
			OnChangeHP(-damage);

			// 체력이 0인 경우 Dead 상태로 전환
			//if (GetCurrentHP() == 0) GetComponent<FSM>()->ChangeState(OBJECT_STATE::DEAD_BEFORE);
		}
	}
}

// 입력 키 - 스킬 발동 pair 추가
void Player::AddSkillKeyMap(KEY_CODE keyCode, ActiveSkill& skill)
{
	auto pair = skillKeyMap.find(keyCode);

	if (pair != skillKeyMap.end()) pair->second = &skill;
	else skillKeyMap.insert(make_pair(keyCode, &skill));
}