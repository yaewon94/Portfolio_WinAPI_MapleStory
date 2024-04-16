#include "PCH.h"
#include "DataManager.h"
#include "AssetManager.h"
#include "MapManager.h"
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
	AssetManager::GetInstance().Init();
	MapManager::GetInstance().Init();
	SkillManager::GetInstance().Init();
}