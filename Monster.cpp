#include "PCH.h"
#include "Monster.h"
#include "Collider.h"
#include "LevelManager.h"

// static 필드 초기화
GameObject* Monster::player = nullptr;

// 생성자
Monster::Monster(const wstring& name, Vec2<float> pos, Vec2<int> scale, float detectRange)
	: AliveObject(name, pos, scale, LAYER_TYPE::ENEMY, 100.f), detectRange(detectRange)
{
}

// 복사 생성자
Monster::Monster(const Monster& origin) : AliveObject(origin), detectRange(origin.detectRange)
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
	if (player == nullptr) player = LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER);

	// 컴포넌트 추가
	// 일부 컴포넌트는 현재 레벨의 Enter()에서 추가함
	Collider* collider = AddComponent<Collider>();

	// 최상위 부모 Init() 호출
	GameObject::Init();
}

// 충돌 진입
void Monster::OnCollisionEnter(GameObject& other)
{
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