#include "PCH.h"
#include "DebugRender.h"
#include "Collider.h"
#include "Engine.h"
#include "LevelManager.h"
#include "Player.h"
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

	for (auto collider : colliders)
	{
		collider = nullptr;
	}
}

// �ʱ�ȭ
void DebugRender::Init()
{
	// ��� �ʱ�ȭ
	//player = (Player*)LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER);

	// ������ ���� �ʱ�ȭ
	//renderLogs.push_back(new Log(LOG_TYPE::LOG, L"", Vec2(100, 50)));
	renderLogs.push_back(new Log(LOG_TYPE::LOG, L"FPS : ", Vec2(100, 100)));
}

// �� �����Ӹ��� ȣ��
void DebugRender::FinalTick()
{
	size_t index = 0;
	// �α� ���� ����
	// �����ͷ� �����Ѽ� �ٲٸ� �ʱ� ���ڿ� ���� ������ �Ѿ ������ ���� �����ͱ��� �ٲ� �� �����Ƿ�, �Ź� ���ο� wstring�� �ѱ��
	// [����] => �̰� �޸𸮿� �δ� �Ȱ�??
	//renderLogs[index++]->SetMessage(player->logtext);
	renderLogs[index++]->SetMessage(L"FPS : " + std::to_wstring(TimeManager::GetInstance().GetFPS()));
}

// �� �����Ӹ��� ������
void DebugRender::Render()
{
	HDC subDC = Engine::GetInstance().GetSubDC();
	Vec2 pos, scale;

	for (auto log : renderLogs)
	{
		Engine::GetInstance().Render(log->GetPos(), log->GetText());
	}

	for (auto collider : colliders)
	{
		HGDIOBJ prevBrush = SelectObject(subDC, (HBRUSH)GetStockObject(HOLLOW_BRUSH));
		HGDIOBJ prevPen = SelectObject(subDC, CreatePen(PS_SOLID, 1, RGB(0, 255, 0)));

		pos = collider->GetRenderPos();
		scale = collider->GetScale();
		Rectangle(subDC
			, pos.x, pos.y
			, pos.x+scale.x, pos.y+scale.y);

		SelectObject(subDC, prevBrush);
		SelectObject(subDC, prevPen);
	}
}