#include "PCH.h"
#include "DataManager.h"
#include "SkillManager.h"

// ������
DataManager::DataManager()
{
}

// �Ҹ���
DataManager::~DataManager()
{
}

// �ʱ�ȭ
void DataManager::Init()
{
	// [�ӽ� �ϵ��ڵ� : �ð��Ǹ� ���� json�̳� DB���� �������� ������� ���� ����]
	SkillManager::GetInstance().Init();
}