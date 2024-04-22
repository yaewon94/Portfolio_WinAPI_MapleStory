#pragma once
#include "Asset.h"

class Sound : public Asset
{
    friend class AssetManager;
    NO_CSTR_COPY_ASSIGN(Sound);

private:
    LPDIRECTSOUNDBUFFER	soundBuffer;
    DSBUFFERDESC bufferInfo;
    int	volume;

private:
    Sound(const wstring& key, const wstring& relativePath);
    ~Sound();

public:
    virtual int Load(const wstring& absolutePath) override;

public:
    // 사운드 재생
    void Play(bool isLoop);

    // 배경음악으로 재생
    void PlayToBGM(bool isLoop=true);

    // 정지
    void Stop(bool isReset);

    // 볼륨 설정 (0 ~ 100)
    void SetVolume(float volume);

    // 사운드 재생 위치 (0 ~ 100)
    void SetPosition(float pos); // 0 ~ 100 

    int GetDecibel(float volume);

private:
    bool LoadWaveSound(const wstring& absolutePath);
};

