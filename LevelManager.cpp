#include "PCH.h"
#include "LevelManager.h"
#include "Level.h"
#include "Level_Test.h"
#include "GameObject.h"

// ������
LevelManager::LevelManager() : level_ID(LEVEL_TYPE::NONE), curLevel(nullptr)
{
}

// �Ҹ���
LevelManager::~LevelManager()
{
	if (curLevel != nullptr)
	{
		curLevel->DeleteObjects();
		delete curLevel;
		curLevel = nullptr;
	}
}

// �ʱ�ȭ
void LevelManager::Init()
{
	// �ʱ� ���� ����
	ChangeLevel(LEVEL_TYPE::TEST);
}

// �� �����Ӹ��� ȣ��
void LevelManager::Tick()
{
	assert(curLevel);
	curLevel->Tick();
}

// �� �����Ӹ��� ȣ��
void LevelManager::FinalTick()
{
	curLevel->FinalTick();
}

// �� �����Ӹ��� ȣ��
void LevelManager::Render()
{
	curLevel->Render();
}

// ���� ��ȯ
void LevelManager::ChangeLevel(LEVEL_TYPE level)
{
	if (level_ID == level)
	{
		//Log(LOG_TYPE::LOG_ERROR, L"���� ������ �����Ϸ��� ������ �����ϴ�");
		return;
	}

	// ���� ���� Exit()
	if (curLevel != nullptr) curLevel->Exit();

	// ���� ��ȯ
	switch (level)
	{
	case LEVEL_TYPE::TEST:
		curLevel = new Level_Test;
		break;
	default:
		//Log(LOG_TYPE::LOG_ERROR, L"�ٲٷ��� ������ �����ϴ�");
		break;
	}

	// ���� ���� Enter(), �ʱ�ȭ
	curLevel->Enter();
	curLevel->Init();
}

// ���� ������ ������Ʈ ã��
GameObject* LevelManager::FindObject(LAYER_TYPE layer)
{
	assert(curLevel);
	return curLevel->FindObject(layer);
}