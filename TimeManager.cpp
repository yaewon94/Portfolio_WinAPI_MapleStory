#include "PCH.h"
#include "TimeManager.h"

// ������
TimeManager::TimeManager() : curCount{}, prevCount{}, frequency{}, deltaTime(0.f), fps(0)
{
}

// �Ҹ���
TimeManager::~TimeManager()
{
}

// �ʱ�ȭ
void TimeManager::Init()
{
	// �ʴ� ī��Ʈ ���
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&curCount);
	prevCount = curCount;
	second = (float)GetTickCount() / 1000;
}

// �� �����Ӹ��� ȣ��
void TimeManager::Tick()
{
	static UINT fpsCal = 0;
	static float time = 0.f;

	// ���� ī��Ʈ ���
	QueryPerformanceCounter(&curCount);
	second = (float)GetTickCount() / 1000;

	// ���� ī��Ʈ�� ���� ī��Ʈ�� ���̰��� ���ؼ� 1������ ���� �ð����� ���
	deltaTime = (float)(curCount.QuadPart - prevCount.QuadPart) / (float)frequency.QuadPart;

	// DT ����
	if (deltaTime > 1.f / 60.f) deltaTime = 1.f / 60.f;

	// ���� ī��Ʈ ����
	prevCount = curCount;

	// �ʴ� ���� Ƚ��(FPS) ���
	++fpsCal;
	time += deltaTime;
	if (time > 1.f)
	{
		fps = fpsCal;
		time = 0.f;
		fpsCal = 0;
	}
}