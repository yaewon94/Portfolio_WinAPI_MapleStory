#pragma once

class Skill;
class ActiveSkill;

class SkillManager final
{
	SINGLETON(SkillManager);

private:
	vector<Skill*> skills;
	map<KEY_CODE, ActiveSkill*> skillKeyMap;

public:
	void Init();

	Skill& GetSkill(size_t index) { return *skills.at(index); }
	ActiveSkill* GetSkill(KEY_CODE keyCode) { return skillKeyMap.find(keyCode)->second; }

private:
	// ========== 스킬 콜백함수 모음 ==========
	//static void ExecuteAttackSkill(Skill& skill);
};