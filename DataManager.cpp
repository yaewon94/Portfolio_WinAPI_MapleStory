#include "PCH.h"
#include "DataManager.h"
#include "AssetManager.h"
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
	AssetManager::GetInstance().Init();
	// [�ӽ� �ϵ��ڵ� : �ð��Ǹ� ���� json�̳� DB���� �������� ������� ���� ����]
	SkillManager::GetInstance().Init();
}