#pragma once
#include "Level.h"

class GameObject;

// 레벨 관리 클래스
class LevelManager final
{
	SINGLETON(LevelManager);

private:
	LEVEL_TYPE level_ID;
	Level* curLevel;

public:
	void Init();
	void Tick();
	void FinalTick();
	void Render();

	void ChangeLevel(LEVEL_TYPE level);

	void AddObject(GameObject& obj);
	GameObject* FindObject(LAYER_TYPE layer);
	GameObject* FindObject(GameObject& obj);
	vector<GameObject*>& FindObjects(LAYER_TYPE layer);
	void DeleteObject(GameObject& obj);

	Camera* GetMainCamera() { return curLevel->mainCamera; }

	// TODO : 보스 레이드 전용 레벨 포인터로 캐스팅해서, 성공했을 때만 호출해야 함
	void OnAlertBossHPzero() { assert(curLevel); curLevel->OnAlertBossHpZero(); }
	void OnChangeGaugePercent(int currentSkillCost) { assert(curLevel); curLevel->OnChangeGaugePercent(currentSkillCost); }
};