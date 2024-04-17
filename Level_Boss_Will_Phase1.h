#pragma once
#include "Level.h"

class ActiveSkill;
class GameObject;

// ���
#define GAUGE_POS Vec2(120.f, 200.f)			// �޺������� ��ǥ
#define GAUGE_SCALE Vec2(150, 150)				// �޺������� ũ��
constexpr auto INTERVAL_OF_FILL_GAUGE = 10.f;	// �޺������� ȸ�� �ֱ� (��)
constexpr auto RECOVERY_AMOUNT_OF_GAUGE = 20;	// �ѹ��� ȸ���Ǵ� �޺���������

// �� 1������
class Level_Boss_Will_Phase1 final : public Level
{
	friend class LevelManager;

private:
	ActiveSkill* gauge_skill = nullptr;
	GameObject* gauge_percent = nullptr; 
	GameObject* gauge_state = nullptr;
	//Texture* textureBufferTest;

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