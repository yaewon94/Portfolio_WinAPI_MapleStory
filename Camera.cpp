#include "PCH.h"
#include "Camera.h"
#include "Engine.h"
#include "LevelManager.h"
#include "GameObject.h"

// ������
Camera::Camera() : resolution(Engine::GetInstance().GetResolution()), player(nullptr)
{
}

// �Ҹ���
Camera::~Camera()
{
}

// �ʱ�ȭ
void Camera::Init()
{
	player = LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER);
}

// �� �����Ӹ��� ȣ��
void Camera::FinalTick()
{
	// �÷��̾ ȭ���� �߾ӿ� ������ ī�޶� ��ǥ ����
	diff.x = player->GetPos().x + (player->GetScale().x * 0.5f) - (resolution.x * 0.5f);
	diff.y = player->GetPos().y + (player->GetScale().y * 0.5f) - (resolution.y * 0.5f);
}