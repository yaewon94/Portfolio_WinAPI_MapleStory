#include "PCH.h"
#include "LevelManager.h"
#include "Level_Boss_Will_Phase1.h"
#include "DataManager.h"
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
	// ������ �ʱ�ȭ
	DataManager::GetInstance().Init();

	// �ʱ� ���� ����
	ChangeLevel(LEVEL_TYPE::BOSS_WILL_PHASE1);
}

// �� �����Ӹ��� ȣ��
void LevelManager::Tick()
{
	assert(curLevel);
	curLevel->Tick();
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

	array<vector<GameObject*>, (size_t)LAYER_TYPE::LAYER_TYPE_COUNT> prevObjects;

	// ���� ���� Exit()
	if (curLevel != nullptr)
	{
		curLevel->Exit();

		// ���� �������� ������ ���� ������Ʈ ����
		for (int layer=0; layer<prevObjects.size(); ++layer)
		{
			for (auto object : curLevel->objects.at(layer))
			{
				prevObjects.at(layer).push_back(object);
			}
		}

		delete curLevel;
	}

	// ���� ��ȯ
	switch (level)
	{
	case LEVEL_TYPE::BOSS_WILL_PHASE1:
		curLevel = new Level_Boss_Will_Phase1;
		break;
	default:
		Log(LOG_TYPE::LOG_ERROR, L"�ٲٷ��� ������ �����ϴ�");
		return;
	}

	// ���� ������ �����ִ� ������Ʈ �ű��
	for (int layer=0; layer<prevObjects.size(); ++layer)
	{
		for (auto object : prevObjects.at(layer))
		{
			curLevel->objects.at(layer).push_back(object);
		}
	}

	// ���� ���� Enter(), �ʱ�ȭ
	curLevel->Enter();
	curLevel->Init();
}

// ���� ������ ������Ʈ �߰�
void LevelManager::AddObject(GameObject& obj)
{
	if(curLevel != nullptr) curLevel->objects[(size_t)obj.GetLayer()].push_back(&obj);
}

// ���� ������ ������Ʈ ã��
GameObject* LevelManager::FindObject(LAYER_TYPE layer)
{
	assert(curLevel);
	return curLevel->objects[(size_t)layer].at(0);
}

GameObject* LevelManager::FindObject(GameObject& obj)
{
	if (curLevel != nullptr)
	{
		for (auto item : curLevel->objects[(size_t)obj.GetLayer()])
		{
			if (&obj == item) return item;
		}
	}

	return nullptr;
}

vector<GameObject*>& LevelManager::FindObjects(LAYER_TYPE layer)
{
	assert(curLevel);

	return curLevel->objects[(size_t)layer];
}

// ���� ������ ������Ʈ ��Ͽ����� ����
// ���� ��ü�� �����ϴ°��� �ƴ�
void LevelManager::DeleteObjectFromList(GameObject& obj)
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