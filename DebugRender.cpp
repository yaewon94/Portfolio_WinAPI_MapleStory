#include "PCH.h"
#include "DebugRender.h"
#include "Collider.h"
#include "Engine.h"
#include "LevelManager.h"
#include "Player.h"
#include "TimeManager.h"

// 생성자
DebugRender::DebugRender() : isRender(true)
{
}

// 소멸자
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

// 초기화
void DebugRender::Init()
{
	// 렌더링 정보 초기화
	renderLogs.push_back(new Log(LOG_TYPE::LOG, L"FPS : ", Vec2(100.f, 100.f)));
	//renderLogs.push_back(new Log(LOG_TYPE::LOG, L"Player RealPos : ", Vec2(100.f, 500.f)));
	//renderLogs.push_back(new Log(LOG_TYPE::LOG, L"Player RenderPos : ", Vec2(100.f, 550.f)));
}

// 매 프레임마다 호출
void DebugRender::FinalTick()
{
	//static Player* player = (Player*)LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER);
	size_t index = 0;

	// 로그 정보 갱신
	renderLogs[index++]->SetMessage(L"FPS : " + std::to_wstring(TimeManager::GetInstance().GetFPS()));
}

// 매 프레임마다 렌더링
void DebugRender::Render()
{
	if (isRender)
	{
		HDC dc = Engine::GetInstance().GetSubDC();
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
				USE_BRUSH(dc, HOLLOW);
				USE_PEN(dc, RED);

				pos = collider->GetRenderPos();
				halfScale = collider->GetScale() * 0.5f;

				Rectangle(dc
					, (int)(pos.x - halfScale.x), (int)(pos.y - halfScale.y)
					, (int)(pos.x + halfScale.x), (int)(pos.y + halfScale.y));
			}
		}
	}
}