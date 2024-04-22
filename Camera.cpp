#include "PCH.h"
#include "Camera.h"
#include "AssetManager.h"
#include "Engine.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "Map.h"
#include "Texture.h"

// �ҽ����� ��������
static float mapLeftLimit, mapRightLimit, mapTopLimit, mapBottomLimit;

// ������
Camera::Camera()
	: resolution(Engine::GetInstance().GetResolution())
	, player(nullptr), currentMap(nullptr), fadeTex(nullptr)
{
}

// �Ҹ���
Camera::~Camera()
{
	player = nullptr;
	currentMap = nullptr;
	fadeTex = nullptr;	// �ؽ�ó ���Ŵ� ���¸Ŵ����� ���
}

// �ʱ�ȭ
void Camera::Init()
{
	player = LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER);
	fadeTex = AssetManager::GetInstance().LoadTexture(L"FadeTexture", L"FadeTexture.png");

	// diff�� ���� ���� ������ ���� (Init�� SetCurrentMap ù��° ȣ�⺸�� ���߿� ȣ���)
	AdjustDiffToMap();
}

// �� �����Ӹ��� ȣ��
void Camera::FinalTick()
{
	float prevDiffX = diff.x;
	float prevDiffY = diff.y;

	// �÷��̾ ȭ���� �߾ӿ� ������ ���� ��ǥ�� ������ ��ǥ ���̰� ����
	diff.x = player->GetRealPos().x + (player->GetScale().x - resolution.x) * 0.5f;
	diff.y = player->GetRealPos().y + (player->GetScale().y - resolution.y) * 0.5f;

	// ���̰��� �� ������ ������ ������� Ȯ��
	if (diff.y < mapTopLimit || diff.y > mapBottomLimit) diff.y = prevDiffY;
	if (diff.x < mapLeftLimit || diff.x > mapRightLimit) diff.x = prevDiffX;

	// ���� �ٲ�� ���̵� ��-�ƿ� ȿ��
	if (useFadeTex)
	{
		if (isFadeIn)
		{
			if (curAlpha < MAX_ALPHA) fadeTex->SetAlpha(curAlpha+=5);
			else isFadeIn = false;
		}
		else
		{
			fadeTex->SetAlpha(curAlpha-=5);
			if (curAlpha <= 0) useFadeTex = false;
		}
	}
}

// ������ (�� �����Ӹ��� ȣ��)
void Camera::Render()
{
	if (useFadeTex) fadeTex->Render(0, 0, 1920, 1080);
}

// ���� �� ����
void Camera::SetCurrentMap(Map* map)
{
	currentMap = map;
	AdjustDiffToMap();
	SetFadeOut();
}

// ���̵� �� ����
void Camera::SetFadeIn()
{
	useFadeTex = true;
	curAlpha = 0;
	isFadeIn = true;
}

// ���̵� �ƿ� ����
void Camera::SetFadeOut()
{
	useFadeTex = true;
	curAlpha = MAX_ALPHA;
	isFadeIn = false;
}

// diff�� ���� ������ ����� (�� ���� ���������� �ʵ���)
void Camera::AdjustDiffToMap()
{
	float mapHalfScaleX = currentMap->GetScale().x * 0.5f;
	float mapHalfScaleY = currentMap->GetScale().y * 0.5f;

	// �÷��̾ ȭ���� �߾ӿ� ������ ���� ��ǥ�� ������ ��ǥ ���̰� ����
	if(player != nullptr)
	{
		diff.x = player->GetRealPos().x + (player->GetScale().x - resolution.x) * 0.5f;
		diff.y = player->GetRealPos().y + (player->GetScale().y - resolution.y) * 0.5f;
	}

	// x��
	if (diff.x < (mapLeftLimit = currentMap->GetPos().x - mapHalfScaleX)) diff.x = mapLeftLimit;
	else if (diff.x > (mapRightLimit = currentMap->GetPos().x + mapHalfScaleX - resolution.x)) diff.x = mapRightLimit;

	// y��
	if (diff.y < (mapTopLimit = currentMap->GetPos().y - mapHalfScaleY)) diff.y = mapTopLimit;
	else if (diff.y > (mapBottomLimit = currentMap->GetPos().y + mapHalfScaleY - resolution.y)) diff.y = mapBottomLimit;
}