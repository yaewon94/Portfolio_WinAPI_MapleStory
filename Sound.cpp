#include "PCH.h"
#include "Sound.h"
#include "SoundManager.h"

// 생성자
Sound::Sound(const wstring& key, const wstring& relativePath) 
	: Asset(key, relativePath)
{
}

// 소멸자
Sound::~Sound()
{
}

// 사운드 로딩
int Sound::Load(const wstring& absolutePath)
{
	// 사운드 디바이스 생성
	if(nullptr == SoundManager::GetInstance().GetSoundDevice()) assert(nullptr);

	wchar_t szExt[10] = { 0 };
	_wsplitpath_s(absolutePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 10);

	// .wav 파일로 가져옴
	if (!wcscmp(szExt, L".wav"))
	{
		if (false == LoadWaveSound(absolutePath)) assert(nullptr);
	}
	else
	{
		assert(nullptr);
	}

	return true;
}

// 사운드 재생
void Sound::Play(bool isLoop)
{
	soundBuffer->SetCurrentPosition(0);

	if (isLoop) soundBuffer->Play(0, 0, DSBPLAY_LOOPING);
	else soundBuffer->Play(0, 0, 0);
}

// 배경음악으로 재생
void Sound::PlayToBGM(bool isLoop)
{
	SoundManager::GetInstance().RegisterToBGM(this);

	if (isLoop) soundBuffer->Play(0, 0, DSBPLAY_LOOPING);
	else soundBuffer->Play(0, 0, 0);
}

// 사운드 정지
void Sound::Stop(bool isReset)
{
	soundBuffer->Stop();
	if (isReset) soundBuffer->SetCurrentPosition(0);
}

// 볼륨 설정
void Sound::SetVolume(float volume)
{
	volume = GetDecibel(volume);
	soundBuffer->SetVolume(volume);
}

// 사운드 재생 위치
void Sound::SetPosition(float pos)
{
	Stop(true);

	DWORD dwBytes = (DWORD)((pos / 100.f) * (float)bufferInfo.dwBufferBytes);
	soundBuffer->SetCurrentPosition(dwBytes);
}

// 볼륨->데시벨 변환
int Sound::GetDecibel(float volume)
{
	if (volume > 100.f) volume = 100.f;
	else if (volume <= 0.f) volume = 0.00001f;

	// 1 ~ 100 의 값을 데시벨로 변환
	int decibel = (LONG)(-2000.0 * log10(100.f / volume));

	if (decibel < -10000) decibel = -10000;
	return  decibel;
}

// .wav 타입으로 로딩
bool Sound::LoadWaveSound(const wstring& absolutePath)
{
	HMMIO	hFile; // File Handle
	wstring strFilePath = absolutePath;

	//CreateFile
	hFile = mmioOpen((wchar_t*)strFilePath.c_str(), NULL, MMIO_READ);// wave 파일 열기

	if (nullptr == hFile)
	{
		// 사운드 로딩 실패
		assert(nullptr);
	}

	// Chunk, wave 파일 구조 분석
	MMCKINFO	pParent;
	memset(&pParent, 0, sizeof(pParent));
	pParent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmioDescend(hFile, &pParent, NULL, MMIO_FINDRIFF);

	MMCKINFO	pChild;
	memset(&pChild, 0, sizeof(pChild));
	pChild.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(hFile, &pChild, &pParent, MMIO_FINDCHUNK);

	WAVEFORMATEX	wft;
	memset(&wft, 0, sizeof(wft));
	mmioRead(hFile, (char*)&wft, sizeof(wft));

	mmioAscend(hFile, &pChild, 0);
	pChild.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(hFile, &pChild, &pParent, MMIO_FINDCHUNK);

	memset(&bufferInfo, 0, sizeof(DSBUFFERDESC));
	bufferInfo.dwBufferBytes = pChild.cksize;
	bufferInfo.dwSize = sizeof(DSBUFFERDESC);
	bufferInfo.dwFlags = DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLVOLUME;
	bufferInfo.lpwfxFormat = &wft;

	if (FAILED(SoundManager::GetInstance().GetSoundDevice()->CreateSoundBuffer(&bufferInfo, &soundBuffer, NULL)))
	{
		// .wav 파일 로딩 실패
		assert(nullptr);
	}

	void* pWrite1 = NULL;
	void* pWrite2 = NULL;
	DWORD dwlength1, dwlength2;

	soundBuffer->Lock(0, pChild.cksize, &pWrite1, &dwlength1, &pWrite2, &dwlength2, 0L);

	if (pWrite1 != nullptr) mmioRead(hFile, (char*)pWrite1, dwlength1);
	if (pWrite2 != nullptr) mmioRead(hFile, (char*)pWrite2, dwlength2);

	soundBuffer->Unlock(pWrite1, dwlength1, pWrite2, dwlength2);

	mmioClose(hFile, 0);

	// 기본 볼륨 50으로 설정
	SetVolume(20.f);

	return true;
}