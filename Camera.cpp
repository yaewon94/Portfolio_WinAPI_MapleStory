#include "PCH.h"
#include "Camera.h"
#include "Engine.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "Map.h"

// �ҽ����� ��������
static float mapHalfScaleX = 0.f;
static float mapHalfScaleY = 0.f;

// ������
Camera::Camera()
	: resolution(Engine::GetInstance().GetResolution())
	, player(nullptr), currentMap(nullptr)
{
}

// �Ҹ���
Camera::~Camera()
{
	player = nullptr;
	currentMap = nullptr;
}

// �ʱ�ȭ
void Camera::Init()
{
	player = LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER);
}

// �� �����Ӹ��� ȣ��
void Camera::FinalTick()
{
	float prevDiffX = diff.x;
	float prevDiffY = diff.y;

	// �÷��̾ ȭ���� �߾ӿ� ������ ���� ��ǥ�� ������ ��ǥ ���̰� ����
	diff.x = player->GetPos().x + (player->GetScale().x - resolution.x) * 0.5f;
	diff.y = player->GetPos().y + (player->GetScale().y - resolution.y) * 0.5f;

	// ���̰��� �� ������ ������ ������� Ȯ��
	if (diff.x < currentMap->GetPos().x - mapHalfScaleX
		|| diff.x > currentMap->GetPos().x + mapHalfScaleX - resolution.x) diff.x = prevDiffX;
	if (diff.y < currentMap->GetPos().y - mapHalfScaleY
		|| diff.y > currentMap->GetPos().y + mapHalfScaleY - resolution.y) diff.y = prevDiffY;
}

// ���� �� ����
void Camera::SetCurrentMap(Map* map)
{
	currentMap = map;
	mapHalfScaleX = currentMap->GetScale().x * 0.5f;
	mapHalfScaleY = currentMap->GetScale().y * 0.5f;

	// diff�� ���� ������ �����ش�
	float left, right, top, bottom;
	if (diff.x < (left = currentMap->GetPos().x - mapHalfScaleX)) diff.x = left;
	else if (diff.x > (right = currentMap->GetPos().x + mapHalfScaleX - resolution.x)) diff.x = right;
	if (diff.y < (top = currentMap->GetPos().y - mapHalfScaleY)) diff.y = top;
	else if (diff.y > (bottom = currentMap->GetPos().y + mapHalfScaleY - resolution.y)) diff.y = bottom;
}