#include "PCH.h"
#include "LevelManager.h"
#include "Level_Boss_Will_Phase1.h"
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
		Log(LOG_TYPE::LOG_ERROR, L"���� ������ �����Ϸ��� ������ �����ϴ�");
		return;
	}

	// ���� ���� Exit()
	if (curLevel != nullptr) curLevel->Exit();

	// ���� ��ȯ
	switch (level)
	{
	case LEVEL_TYPE::TEST:
		curLevel = new Level_Boss_Will_Phase1;
		break;
	default:
		Log(LOG_TYPE::LOG_ERROR, L"�ٲٷ��� ������ �����ϴ�");
		break;
	}

	// ���� ���� Enter(), �ʱ�ȭ
	curLevel->Enter();
	curLevel->Init();
}

// ���� ������ ������Ʈ �߰�
void LevelManager::AddObject(GameObject& obj)
{
	assert(curLevel);
	curLevel->objects[(size_t)obj.GetLayer()].push_back(&obj);
}

// ���� ������ ������Ʈ ã��
GameObject* LevelManager::FindObject(LAYER_TYPE layer)
{
	assert(curLevel);
	return curLevel->objects[(size_t)layer].at(0);
}

GameObject* LevelManager::FindObject(GameObject& obj)
{
	assert(curLevel);

	for (auto item : curLevel->objects[(size_t)obj.GetLayer()])
	{
		if (&obj == item) return item;
	}

	return nullptr;
}

// ���� ������ ������Ʈ ��Ͽ��� ����
void LevelManager::DeleteObject(GameObject& obj)
{
	assert(curLevel);
	auto& items = curLevel->objects[(size_t)obj.GetLayer()];
	auto iter = items.begin();

	for (; iter != items.end(); ++iter)
	{
		if (&obj == *iter)
		{
			items.erase(iter);
			return;
		}
	}
}