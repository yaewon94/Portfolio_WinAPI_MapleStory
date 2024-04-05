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
	renderLogs.push_back(new Log(LOG_TYPE::LOG, L"", Vec2(100, 100)));
}

// �� �����Ӹ��� ȣ��
void DebugRender::FinalTick()
{
	// �α� ���� ����
	// �����ͷ� �����Ѽ� �ٲٸ� �ʱ� ���ڿ� ���� ������ �Ѿ ������ ���� �����ͱ��� �ٲ� �� �����Ƿ�, �Ź� ���ο� wstring�� �ѱ��
	// [����] => �̰� �޸𸮿� �δ� �Ȱ�??
	//renderLogs[0]->SetMessage(L"Player pos = " + ::to_wstring(player->GetPos()));
	renderLogs[0]->SetMessage(L"FPS : " + std::to_wstring(TimeManager::GetInstance().GetFPS()));
	//assert(nullptr);
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