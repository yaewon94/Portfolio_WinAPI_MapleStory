#include "PCH.h"
#include "SoundManager.h"
#include "Sound.h"
#include "Engine.h"

// 생성자
SoundManager::SoundManager() : sound(nullptr), bgm(nullptr)
{
}

// 소멸자
SoundManager::~SoundManager()
{
	// DirectSound8 객체 메모리 해제
	sound->Release();
}

// 초기화
int SoundManager::Init()
{
	if (FAILED(DirectSoundCreate8(NULL, &sound, NULL)))
	{
		// 사운드 디바이스 생성 실패
		assert(nullptr);
	}

	// 사운드 협조레벨 설정
	HWND hWnd = Engine::GetInstance().GetMainWindow();
	if (FAILED(sound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE)))
	{
		// 사운드 매니저 초기화 실패
		assert(nullptr);
	}

	return true;
}

// BGM 으로 등록
void SoundManager::RegisterToBGM(Sound* sound)
{
	if (bgm != nullptr) bgm->Stop(true);
	bgm = sound;
}