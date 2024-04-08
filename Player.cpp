#include "PCH.h"
#include "Player.h"
#include "Rigidbody.h"
#include "SkillManager.h"
#include "SkillObject.h"

// 생성자
Player::Player(const wstring& name, Vec2 pos, Vec2 scale) : AliveObject(name, pos, scale, LAYER_TYPE::PLAYER)
{
	// 스킬오브젝트를 자식 오브젝트로 추가
	AddChild(SkillObject(L"", Vec2(scale.x, scale.y * 0.5f), Vec2(20, 20), LAYER_TYPE::PLAYER_SKILL));
}

// 복사 생성자
Player::Player(const Player& origin) : AliveObject(origin)
{
}

// 소멸자
Player::~Player()
{
}

// 초기화
void Player::Init()
{
	// 스킬 오브젝트 설정
	SetSkillObject(*(SkillObject*)GetChild(LAYER_TYPE::PLAYER_SKILL));

	// [CHECK] 스킬 추가 (임시 하드코딩)
	AddSkill(SkillManager::GetInstance().GetSkill(0));
}

// 이번 프레임에 처음 눌렸을 때 호출
void Player::OnKeyPressed(KEY_CODE key)
{
	// [check] 키세팅 커스터마이징 할 때는 자기가 셋팅한 키값대로 분기시켜야 함
	switch (key)
	{
	case KEY_CODE::SHIFT:
		// TODO : 스킬사용 호출
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

// 저번 프레임에도 눌리고, 이번 프레임에도 눌렸을 때 호출
void Player::OnKeyDown(KEY_CODE key)
{
	if (key == KEY_CODE::LEFT || key == KEY_CODE::RIGHT) Move();
}