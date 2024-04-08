#include "PCH.h"
#include "Player.h"
#include "Rigidbody.h"
#include "SkillManager.h"
#include "SkillObject.h"

// ������
Player::Player(const wstring& name, Vec2 pos, Vec2 scale) : AliveObject(name, pos, scale, LAYER_TYPE::PLAYER)
{
	// ��ų������Ʈ�� �ڽ� ������Ʈ�� �߰�
	AddChild(SkillObject(L"", Vec2(scale.x, scale.y * 0.5f), Vec2(20, 20), LAYER_TYPE::PLAYER_SKILL));
}

// ���� ������
Player::Player(const Player& origin) : AliveObject(origin)
{
}

// �Ҹ���
Player::~Player()
{
}

// �ʱ�ȭ
void Player::Init()
{
	// ��ų ������Ʈ ����
	SetSkillObject(*(SkillObject*)GetChild(LAYER_TYPE::PLAYER_SKILL));

	// [CHECK] ��ų �߰� (�ӽ� �ϵ��ڵ�)
	AddSkill(SkillManager::GetInstance().GetSkill(0));
}

// �̹� �����ӿ� ó�� ������ �� ȣ��
void Player::OnKeyPressed(KEY_CODE key)
{
	// [check] Ű���� Ŀ���͸���¡ �� ���� �ڱⰡ ������ Ű����� �б���Ѿ� ��
	switch (key)
	{
	case KEY_CODE::SHIFT:
		// TODO : ��ų��� ȣ��
		break;
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