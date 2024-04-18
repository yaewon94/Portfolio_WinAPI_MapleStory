#include "PCH.h"
#include "Monster.h"
#include "AttackActiveSkill.h"
#include "Collider.h"
#include "LevelManager.h"
#include "Player.h"
#include "SkillObject.h"

// static 필드 초기화
Player* Monster::player = nullptr;

// 생성자
Monster::Monster(const wstring& name, int MaxHP)
	: AliveObject(name, LAYER_TYPE::ENEMY, MaxHP, 100.f)
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

// 플레이어 감지
bool Monster::DetectPlayer()
{
	static float playerRad = sqrtf(0.25f * (player->GetScale().x * player->GetScale().x + player->GetScale().y * player->GetScale().y));

	if (GetRealPos().GetDistance(player->GetRealPos()) <= detectRange + playerRad) return true;
	else return false;
}

// 플레이어 추격
bool Monster::Trace()
{
	// 일정 거리 이내까지만 추격
	if (GetRealPos().GetDistance(player->GetRealPos()) <= MAX_TRACE_DISTANCE)
	{
		return false;
	}
	else
	{
		// 방향 설정
		if (GetRealPos().x - player->GetRealPos().x > 0) dir = Vec2<float>::Left();
		else dir = Vec2<float>::Right();

		// 이동
		Move();

		return true;
	}
}