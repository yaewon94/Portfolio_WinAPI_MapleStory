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

// static 필드 초기화
Player* Monster::player = nullptr;

// 생성자
Monster::Monster(const wstring& name, int MaxHP)
	: AliveObject(name, LAYER_TYPE::ENEMY, MaxHP)
{
}

// 복사 생성자
Monster::Monster(const Monster& origin) 
	: AliveObject(origin)
	, detectRange(origin.detectRange)
{
}

// 소멸자
Monster::~Monster()
{
}

// 초기화
void Monster::Init()
{
	// 필드 초기화
	if (player == nullptr) player = static_cast<Player*>(LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER));

	// 컴포넌트 추가
	// 일부 컴포넌트는 현재 레벨의 Enter()에서 추가함
	Collider* collider = AddComponent<Collider>();
	//collider->SetScale(DEFAULT_OBJECT_SCALE);
	FSM* fsm = AddComponent<FSM>();
	fsm->SetDefaultState(OBJECT_STATE::IDLE);
	fsm->AddState(*new MonsterIdleState);
	fsm->AddState(*new MonsterTraceState);
	fsm->AddState(*new MonsterAttackState(3.f));
	fsm->AddState(*new DeadBeforeState(3.f));
	fsm->AddState(*new MonsterDeadState(5.f));

	// TODO : 몬스터 스킬 DB
	// 몬스터마다 보유스킬이 다르므로 임시로 레벨에서 추가해줬음

	// 자식 오브젝트 추가
	SkillObject* skillObject = (SkillObject*)AddChild(SkillObject(L"", Vec2(150.f, 0.f), DEFAULT_OBJECT_SCALE, LAYER_TYPE::ENEMY_SKILL));

	// 필드 초기화
	SetSkillObject(*(SkillObject*)GetChild(LAYER_TYPE::ENEMY_SKILL));

	// 최상위 부모 Init() 호출
	GameObject::Init();
}

// 충돌 진입
void Monster::OnCollisionEnter(GameObject& other)
{
	AliveObject::OnCollisionEnter(other);

	// 플레이어 스킬에 맞았을 경우
	if (other.GetLayer() == LAYER_TYPE::PLAYER_SKILL)
	{
		// 현재 체력이 0 이상일때만
		if (GetCurrentHP() > 0)
		{
			// 입은 데미지만큼 체력 감소시킴
			SkillObject* obj = (SkillObject*)&other;
			int damage = (int)(obj->GetSkill()->GetCoefficient() * player->GetPower());
			OnChangeHP(-damage);

			// TODO : 일반몬스터 클래스와 보스몬스터 클래스를 분리해서 구현해야 함
			// 체력이 0인 경우 보스몬스터 체력 0 알림 호출
			if (GetCurrentHP() == 0) LevelManager::GetInstance().OnAlertBossHPzero();
		}
	}
}

// 충돌 중
void Monster::OnCollisionStay(GameObject& other)
{
}

// 충돌 종료
void Monster::OnCollisionExit(GameObject& other)
{
}

// 공격
void Monster::Attack()
{
	// 몬스터가 가지고 있는 스킬들중 랜덤으로 사용
	int index = RandomManager::Create(GetSkillCount());

	Skill* skill = &GetSkill(index);
	skill->UseSkill(this, (SkillObject*)GetChild(LAYER_TYPE::ENEMY_SKILL));
}

// 플레이어 감지
bool Monster::DetectPlayer()
{
	static float playerRad = sqrtf(0.25f * (player->GetScale().x * player->GetScale().x + player->GetScale().y * player->GetScale().y));

	if (GetRealPos().GetDistance(player->GetRealPos()) <= detectRange + playerRad) return true;
	else return false;
}

// 플레이어 추격
// @ return : 플레이어 근처에 도달했는지 여부
bool Monster::Trace()
{
	// 일정 거리 이내까지만 추격
	if (GetRealPos().GetDistance(player->GetRealPos()) <= MAX_TRACE_DISTANCE)
	{
		return true;
	}
	else
	{
		// 방향 설정
		if (GetRealPos().x - player->GetRealPos().x > 0) dir = Vec2<float>::Left();
		else dir = Vec2<float>::Right();

		// 이동
		Move();

		return false;
	}
}