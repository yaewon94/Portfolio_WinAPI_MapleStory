#pragma once

class TimeManager final
{
	SINGLETON(TimeManager);

private:
	LARGE_INTEGER curCount;
	LARGE_INTEGER prevCount;
	LARGE_INTEGER frequency;
	UINT fps;

	float deltaTime;	// 1 프레임 실행 시간
	float second;	// 시스템 실행 후 경과 시간 (초)

public:
	void Init();
	void Tick();

public:
	float GetDeltaTime() { return deltaTime; }
	UINT GetFPS() { return fps; }
	float GetSecond() { return second; }
};