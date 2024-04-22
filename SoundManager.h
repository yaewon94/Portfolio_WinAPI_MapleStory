#pragma once

class Sound;

// ���� ���� Ŭ����
class SoundManager final
{
	SINGLETON(SoundManager);

private:
	LPDIRECTSOUND8	sound;	// ���� ī�� ����
	Sound* bgm;				// BGM


public:
	int Init();
	LPDIRECTSOUND8 GetSoundDevice() { return sound; }
	void RegisterToBGM(Sound* sound);
};

