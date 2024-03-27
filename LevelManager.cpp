#include "PCH.h"
#include "LevelManager.h"
#include "Level_Test.h"

// ������
LevelManager::LevelManager() : level_ID(LEVEL_TYPE::NONE), curLevel(nullptr)
{
}

// �Ҹ���
LevelManager::~LevelManager()
{
	// �����Ŵ����� �Ҹ��ڰ� ȣ��� ���� ������ ����� �� �̹Ƿ�, ���� ������ ������Ʈ ��� ����
	curLevel->DeleteObjects();

	// �޸� ����
	if (curLevel != nullptr)
	{
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
void LevelManager::ChangeLevel(const LEVEL_TYPE level)
{
	if (level_ID == level) throw GameException(L"���� ������ �����Ϸ��� ������ �����ϴ�");

	// ���� ���� Exit()
	if (curLevel != nullptr)
	{
		curLevel->Exit();
		delete curLevel;
	}

	// ���� ��ȯ
	switch (level)
	{
	case LEVEL_TYPE::TEST:
		curLevel = new Level_Test;
		break;
	default:
		throw GameException(L"�ٲٷ��� ������ �����ϴ�");
		break;
	}

	// ���� ���� Enter(), �ʱ�ȭ
	curLevel->Enter();
	curLevel->Init();
}