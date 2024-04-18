#include "PCH.h"
#include "DebugRender.h"
#include "Collider.h"
#include "Engine.h"
#include "LevelManager.h"
#include "Player.h"
#include "TimeManager.h"

// ������
DebugRender::DebugRender()
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
	// ������ ���� �ʱ�ȭ
	renderLogs.push_back(new Log(LOG_TYPE::LOG, L"FPS : ", Vec2(100.f, 100.f)));
	//renderLogs.push_back(new Log(LOG_TYPE::LOG, L"Player RealPos : ", Vec2(100.f, 500.f)));
	//renderLogs.push_back(new Log(LOG_TYPE::LOG, L"Player RenderPos : ", Vec2(100.f, 550.f)));
}

// �� �����Ӹ��� ȣ��
void DebugRender::FinalTick()
{
	//static Player* player = (Player*)LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER);
	size_t index = 0;

	// �α� ���� ����
	// �����ͷ� �����Ѽ� �ٲٸ� �ʱ� ���ڿ� ���� ������ �Ѿ ������ ���� �����ͱ��� �ٲ� �� �����Ƿ�, �Ź� ���ο� wstring�� �ѱ��
	// [����] => �̰� �޸𸮿� �δ� �Ȱ�??
	renderLogs[index++]->SetMessage(L"FPS : " + std::to_wstring(TimeManager::GetInstance().GetFPS()));
	//renderLogs[index++]->SetMessage(L"Player RealPos : " + player->GetRealPos().to_wstring());
	//renderLogs[index++]->SetMessage(L"Player RenderPos : " + player->GetRenderPos().to_wstring());
}

// �� �����Ӹ��� ������
void DebugRender::Render()
{
	HDC subDC = Engine::GetInstance().GetSubDC();
	Vec2<float> pos;
	Vec2<int> halfScale;

	for (auto log : renderLogs)
	{
		Engine::GetInstance().Render(log->GetPos(), log->GetText());
	}

	for (auto collider : colliders)
	{
		if (collider->IsActive())
		{
			HGDIOBJ prevBrush = SelectObject(subDC, (HBRUSH)GetStockObject(HOLLOW_BRUSH));
			HGDIOBJ prevPen = SelectObject(subDC, CreatePen(PS_SOLID, 1, RGB(0, 255, 0)));

			pos = collider->GetRenderPos();
			halfScale = collider->GetScale() * 0.5f;

			Rectangle(subDC
				, (int)(pos.x - halfScale.x), (int)(pos.y - halfScale.y)
				, (int)(pos.x + halfScale.x), (int)(pos.y + halfScale.y));

			SelectObject(subDC, prevBrush);
			SelectObject(subDC, prevPen);
		}
	}
}