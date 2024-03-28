#include "PCH.h"
#include "DebugRender.h"

#include "Engine.h"
#include "LevelManager.h"

#include "Player.h"

// 생성자
DebugRender::DebugRender() : DC(nullptr), player(nullptr)
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

	renderLogs.clear();
}

// 초기화
void DebugRender::Init()
{
	// 멤버 초기화
	DC = Engine::GetInstance().GetSubDC();
	player = (Player*)(&LevelManager::GetInstance().GetCurrentLevel().FindObject(LAYER_TYPE::PLAYER));

	// 렌더링 정보 초기화
	renderLogs.push_back(new Log{Vec2(10, 10), L"Player pos = "});
}

// 매 프레임마다 호출
void DebugRender::FinalTick()
{
	// 로그 정보 갱신
	// 포인터로 가리켜서 바꾸면 초기 문자열 저장 범위를 넘어서 엉뚱한 곳의 데이터까지 바꿀 수 있으므로, 매번 새로운 wstring를 넘긴다
	// [질문] => 이거 메모리에 부담 안감??
	renderLogs[0]->message = L"Player pos = " + ::to_wstring(player->GetPos());
}

// 매 프레임마다 렌더링
void DebugRender::Render()
{
	SetBkMode(DC, TRANSPARENT);

	// 로그 출력
	for (const auto log : renderLogs)
	{
		TextOutW(DC, log->pos.x, log->pos.y, log->message.c_str(), (int)log->message.length());
	}
}