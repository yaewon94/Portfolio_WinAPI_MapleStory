#include "PCH.h"
#include "DebugRender.h"

#include "Engine.h"
#include "LevelManager.h"

#include "Player.h"

// ������
DebugRender::DebugRender() : DC(nullptr), player(nullptr)
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

	renderLogs.clear();
}

// �ʱ�ȭ
void DebugRender::Init()
{
	// ��� �ʱ�ȭ
	DC = Engine::GetInstance().GetSubDC();
	player = (Player*)(&LevelManager::GetInstance().GetCurrentLevel().FindObject(LAYER_TYPE::PLAYER));

	// ������ ���� �ʱ�ȭ
	renderLogs.push_back(new Log{Vec2(10, 10), L"Player pos = "});
}

// �� �����Ӹ��� ȣ��
void DebugRender::FinalTick()
{
	// �α� ���� ����
	// �����ͷ� �����Ѽ� �ٲٸ� �ʱ� ���ڿ� ���� ������ �Ѿ ������ ���� �����ͱ��� �ٲ� �� �����Ƿ�, �Ź� ���ο� wstring�� �ѱ��
	// [����] => �̰� �޸𸮿� �δ� �Ȱ�??
	renderLogs[0]->message = L"Player pos = " + ::to_wstring(player->GetPos());
}

// �� �����Ӹ��� ������
void DebugRender::Render()
{
	SetBkMode(DC, TRANSPARENT);

	// �α� ���
	for (const auto log : renderLogs)
	{
		TextOutW(DC, log->pos.x, log->pos.y, log->message.c_str(), (int)log->message.length());
	}
}