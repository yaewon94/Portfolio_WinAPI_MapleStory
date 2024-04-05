#pragma once

class TimeManager final
{
	SINGLETON(TimeManager);

private:
	LARGE_INTEGER	curCount;
	LARGE_INTEGER	prevCount;
	LARGE_INTEGER	frequency;
	UINT			fps;

	float			deltaTime;	// 1 프레임 실행 시간

public:
	void Init();
	void Tick();

public:
	float GetDeltaTime() { return deltaTime; }
	UINT GetFPS() { return fps; }
};