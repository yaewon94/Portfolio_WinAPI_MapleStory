#pragma once
#include "GameObject.h"

class Animation;
class AttackSkillModule;
class Skill;

// 스킬오브젝트 클래스
class SkillObject : public GameObject
{
private:
	GameObject& caster;			// 스킬 시전자
	const Vec2<float> Offset;	// 시전자 기준 오프셋
	Vec2<float> velocity;		// 스킬 이동속도 (, 최대 이동거리)
	Vec2<float> startPos;		// 스킬 활성화 되었을 때 시작좌표 (스킬 시전자 좌표 + Offset)

	// ERROR : 설계에러
	// 두개 부모가 달라서 제대로 변환할수가 없음
	AttackSkillModule* attackSkillPtr;	// 현재 스킬에 대한 포인터
	Skill* skillPtr;					// 현재 스킬에 대한 포인터

	float time = 0.f;	// 스킬오브젝트 활성화 이후 경과시간

	// 담당 스킬 모음
	map<int, map<OBJECT_STATE, Animation*>> skillMap;	// key:스킬인덱스, value:상태-애니메이션

public:
	SkillObject(const wstring& name, GameObject& caster, Vec2<float> offset, Vec2<int> scale, LAYER_TYPE layer);
	SkillObject(const SkillObject& origin);
	~SkillObject();
	virtual SkillObject* Clone() override { return new SkillObject(*this); }

	virtual void Init() override;
	virtual void Tick() override;

	virtual void OnCollisionEnter(GameObject& other) override;
	virtual void OnCollisionStay(GameObject& other) override {}
	virtual void OnCollisionExit(GameObject& other) override {}

	void AddSkill(int index);
	AttackSkillModule* GetSkill() { return attackSkillPtr; }

	// ERROR : 스킬클래스 구조 잘못만든듯
	// AttackSkillModule이랑 Skill이랑 완전히 다른 클래스라 형변환이 안됌. 두 포인터 타입으로 다 받아야 함
	void SetSkill(AttackSkillModule* me_attack, Skill* me_skill);
	void SetSkill(AttackSkillModule* me_attack, Skill* me_skill, Vec2<float> velocity);

	virtual void SetActive(bool flag) override;
};