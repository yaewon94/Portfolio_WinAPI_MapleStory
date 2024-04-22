#include "PCH.h"
#include "SoundManager.h"
#include "Sound.h"
#include "Engine.h"

// ������
SoundManager::SoundManager() : sound(nullptr), bgm(nullptr)
{
}

// �Ҹ���
SoundManager::~SoundManager()
{
	// DirectSound8 ��ü �޸� ����
	sound->Release();
}

// �ʱ�ȭ
int SoundManager::Init()
{
	if (FAILED(DirectSoundCreate8(NULL, &sound, NULL)))
	{
		// ���� ����̽� ���� ����
		assert(nullptr);
	}

	// ���� �������� ����
	HWND hWnd = Engine::GetInstance().GetMainWindow();
	if (FAILED(sound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE)))
	{
		// ���� �Ŵ��� �ʱ�ȭ ����
		assert(nullptr);
	}

	return true;
}

// BGM ���� ���
void SoundManager::RegisterToBGM(Sound* sound)
{
	if (bgm != nullptr) bgm->Stop(true);
	bgm = sound;
}