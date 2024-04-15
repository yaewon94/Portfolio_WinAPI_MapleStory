#include "PCH.h"
#include "Monster.h"
#include "Collider.h"
#include "LevelManager.h"

// static �ʵ� �ʱ�ȭ
GameObject* Monster::player = nullptr;

// ������
Monster::Monster(const wstring& name, Vec2 pos, Vec2 scale, int detectRange)
	: AliveObject(name, pos, scale, LAYER_TYPE::ENEMY, 100), detectRange(detectRange)
{
}

// ���� ������
Monster::Monster(const Monster& origin) : AliveObject(origin), detectRange(origin.detectRange)
{
}

// �Ҹ���
Monster::~Monster()
{
}

// �ʱ�ȭ
void Monster::Init()
{
	// �ʵ� �ʱ�ȭ
	if (player == nullptr) player = LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER);

	// ������Ʈ �߰�
	// �Ϻ� ������Ʈ�� ���� ������ Enter()���� �߰���
	Collider* collider = AddComponent<Collider>();

	// �ֻ��� �θ� Init() ȣ��
	GameObject::Init();
}

// �浹 ����
void Monster::OnCollisionEnter(GameObject& other)
{
}

// �浹 ��
void Monster::OnCollisionStay(GameObject& other)
{
}

// �浹 ����
void Monster::OnCollisionExit(GameObject& other)
{
}

// �÷��̾� ����
bool Monster::DetectPlayer()
{
	static int playerRad = (int)sqrtf(0.25f * (player->GetScale().x * player->GetScale().x + player->GetScale().y * player->GetScale().y));

	if (GetPos().GetDistance(player->GetPos()) <= detectRange + playerRad) return true;
	else return false;
}

// �÷��̾� �߰�
bool Monster::Trace()
{
	// ���� �Ÿ� �̳������� �߰�
	if (GetPos().GetDistance(player->GetPos()) <= MAX_TRACE_DISTANCE)
	{
		return false;
	}
	else
	{
		// ���� ����
		if (GetPos().x - player->GetPos().x > 0) dir = Vec2::Left();
		else dir = Vec2::Right();

		// �̵�
		Move();

		return true;
	}
}