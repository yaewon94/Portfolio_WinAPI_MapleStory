#pragma once
#include "Level.h"

class GameObject;

// ���
constexpr auto RECOVERY_AMOUNT_OF_GAUGE = 20;	// �ѹ��� ȸ���Ǵ� �޺���������
constexpr auto INTERVAL_OF_FILL_GAUGE = 10.f;	// �޺������� ȸ�� �ֱ� (��)

// �� 1������
class Level_Boss_Will_Phase1 final : public Level
{
	friend class LevelManager;

private:
	GameObject* gauge_moonlight;

private:
	NO_CSTR_COPY_ASSIGN(Level_Boss_Will_Phase1);
	Level_Boss_Will_Phase1();
	~Level_Boss_Will_Phase1();

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void FinalTick() override;

public:
	virtual void OnChangeGaugePercent(int currentSkillCost) override;
};