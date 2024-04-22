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
    // ���� ���
    void Play(bool isLoop);

    // ����������� ���
    void PlayToBGM(bool isLoop=true);

    // ����
    void Stop(bool isReset);

    // ���� ���� (0 ~ 100)
    void SetVolume(float volume);

    // ���� ��� ��ġ (0 ~ 100)
    void SetPosition(float pos); // 0 ~ 100 

    int GetDecibel(float volume);

private:
    bool LoadWaveSound(const wstring& absolutePath);
};

