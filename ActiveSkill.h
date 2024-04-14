#pragma once
#include "Skill.h"
#include "IKeyEvent.h"

class Player;

// 플레이어가 직접 키를 눌러서 발동하는 스킬의 상위클래스
// [abstract class]
class ActiveSkill : public Skill, public IKeyEvent
{
	NO_CSTR_COPY_ASSIGN(ActiveSkill);

	friend class SkillManager;

	// ===== static 멤버 =====
private:
	static Player* player;

public:
	static void SetPlayer(Player* player) { ActiveSkill::player = player; }

	// ===== 인스턴스 멤버 =====
protected:
	ActiveSkill(const wstring& name);
	~ActiveSkill();

	virtual void OnKeyPressed(KEY_CODE) override {};
	virtual void OnKeyDown(KEY_CODE) override {};
	virtual void OnKeyReleased(KEY_CODE) override {};

	Player& GetPlayer() { return *player; }
};