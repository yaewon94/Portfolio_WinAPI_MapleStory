#include "PCH.h"
#include "DebugRender.h"
#include "Collider.h"
#include "Engine.h"
#include "LevelManager.h"
#include "TimeManager.h"

// 생성자
DebugRender::DebugRender()
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
	renderLogs.push_back(new Log(LOG_TYPE::LOG, L"FPS : ", Vec2(100, 100)));
}

// 매 프레임마다 호출
void DebugRender::FinalTick()
{
	size_t index = 0;
	// 로그 정보 갱신
	// 포인터로 가리켜서 바꾸면 초기 문자열 저장 범위를 넘어서 엉뚱한 곳의 데이터까지 바꿀 수 있으므로, 매번 새로운 wstring를 넘긴다
	// [질문] => 이거 메모리에 부담 안감??
	renderLogs[index++]->SetMessage(L"FPS : " + std::to_wstring(TimeManager::GetInstance().GetFPS()));
}

// 매 프레임마다 렌더링
void DebugRender::Render()
{
	HDC subDC = Engine::GetInstance().GetSubDC();
	Vec2 pos;
	Vec2 halfScale;

	for (auto log : renderLogs)
	{
		Engine::GetInstance().Render(log->GetPos(), log->GetText());
	}

	for (auto collider : colliders)
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