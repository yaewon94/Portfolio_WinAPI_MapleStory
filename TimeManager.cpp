#include "PCH.h"
#include "TimeManager.h"

// 생성자
TimeManager::TimeManager() : curCount{}, prevCount{}, frequency{}, deltaTime(0.f), fps(0)
{
}

// 소멸자
TimeManager::~TimeManager()
{
}

// 초기화
void TimeManager::Init()
{
	// 초당 카운트 얻기
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&curCount);
	prevCount = curCount;
	second = (float)GetTickCount() / 1000;
}

// 매 프레임마다 호출
void TimeManager::Tick()
{
	static UINT fpsCal = 0;
	static float time = 0.f;

	// 현재 카운트 계산
	QueryPerformanceCounter(&curCount);
	second = (float)GetTickCount() / 1000;

	// 이전 카운트와 현재 카운트의 차이값을 통해서 1프레임 간의 시간값을 계산
	deltaTime = (float)(curCount.QuadPart - prevCount.QuadPart) / (float)frequency.QuadPart;

	// DT 보정
	if (deltaTime > 1.f / 60.f) deltaTime = 1.f / 60.f;

	// 이전 카운트 저장
	prevCount = curCount;

	// 초당 실행 횟수(FPS) 계산
	++fpsCal;
	time += deltaTime;
	if (time > 1.f)
	{
		fps = fpsCal;
		time = 0.f;
		fpsCal = 0;
	}
}