#pragma once

class Sound;

// 사운드 관리 클래스
class SoundManager final
{
	SINGLETON(SoundManager);

private:
	LPDIRECTSOUND8	sound;	// 사운드 카드 제어
	Sound* bgm;				// BGM


public:
	int Init();
	LPDIRECTSOUND8 GetSoundDevice() { return sound; }
	void RegisterToBGM(Sound* sound);
};

