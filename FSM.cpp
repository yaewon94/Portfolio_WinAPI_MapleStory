#include "PCH.h"
#include "FSM.h"
#include "State.h"

// ������
FSM::FSM(GameObject& owner) : Component(owner), curState(nullptr)
{
}

// ���� ������
FSM::FSM(const FSM& origin) : Component(origin), curState(nullptr)
{
}

// �Ҹ���
FSM::~FSM()
{
	curState = nullptr;
	// [CHECK] State*�� ����Ű�� ��ü�� ���⼭ ����������, State���� ó���ؾ� ���� �����غ�����
}

// �ʱ�ȭ
void FSM::Init()
{
	// TODO : ���� �߰�

	// IDLE ���¸� ����Ʈ�� ��
	curState = stateMap.find(OBJECT_STATE::IDLE)->second;
}