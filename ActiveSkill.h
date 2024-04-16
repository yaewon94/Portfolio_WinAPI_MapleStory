#pragma once
#include "Skill.h"
#include "IKeyEvent.h"

class Player;

// �÷��̾ ���� Ű�� ������ �ߵ��ϴ� ��ų�� ����Ŭ����
// [abstract class]
class ActiveSkill : public Skill, public IKeyEvent
{
	NO_CSTR_COPY_ASSIGN(ActiveSkill);

	friend class SkillManager;

	// ===== static ��� =====
private:
	static Player* player;

public:
	static void SetPlayer(Player* player) { ActiveSkill::player = player; }

	// ===== �ν��Ͻ� ��� =====
protected:
	const int Cost;	// ��ų ���� �ʿ��� (HP, MP, ������ ��) �Ҹ�

protected:
	ActiveSkill(const wstring& name, int Cost = 0);
	~ActiveSkill();

	virtual void OnKeyPressed(KEY_CODE) override {};
	virtual void OnKeyDown(KEY_CODE) override {};
	virtual void OnKeyReleased(KEY_CODE) override {};

	Player& GetPlayer() { return *player; }
};