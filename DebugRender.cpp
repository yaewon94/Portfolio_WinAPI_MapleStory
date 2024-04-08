#include "PCH.h"
#include "DebugRender.h"
#include "Engine.h"
#include "LevelManager.h"
#include "GameObject.h"
#include "TimeManager.h"

// ������
DebugRender::DebugRender() : player(nullptr)
{
}

// �Ҹ���
DebugRender::~DebugRender()
{
	for (auto log : renderLogs)
	{
		if (log != nullptr)
		{
			delete log;
			log = nullptr;
		}
	}
}

// �ʱ�ȭ
void DebugRender::Init()
{
	// ��� �ʱ�ȭ
	//player = LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER);

	// ������ ���� �ʱ�ȭ
	//renderLogs.push_back(new Log(LOG_TYPE::LOG, L"Player pos : ", Vec2(100, 50)));
	renderLogs.push_back(new Log(LOG_TYPE::LOG, L"FPS : ", Vec2(100, 100)));
}

// �� �����Ӹ��� ȣ��
void DebugRender::FinalTick()
{
	size_t index = 0;
	// �α� ���� ����
	// �����ͷ� �����Ѽ� �ٲٸ� �ʱ� ���ڿ� ���� ������ �Ѿ ������ ���� �����ͱ��� �ٲ� �� �����Ƿ�, �Ź� ���ο� wstring�� �ѱ��
	// [����] => �̰� �޸𸮿� �δ� �Ȱ�??
	//renderLogs[index++]->SetMessage(L"Player pos = " + ::to_wstring(player->GetPos()));
	renderLogs[index++]->SetMessage(L"FPS : " + std::to_wstring(TimeManager::GetInstance().GetFPS()));
}

// �� �����Ӹ��� ������
void DebugRender::Render()
{
	//assert(nullptr);
	for (auto log : renderLogs)
	{
		Engine::GetInstance().Render(log->GetPos(), log->GetText());
	}
}