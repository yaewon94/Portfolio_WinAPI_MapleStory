#include "PCH.h"
#include "Camera.h"
#include "Engine.h"
#include "LevelManager.h"
#include "GameObject.h"

// 생성자
Camera::Camera() : resolution(Engine::GetInstance().GetResolution()), player(nullptr)
{
}

// 소멸자
Camera::~Camera()
{
}

// 초기화
void Camera::Init()
{
	player = LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER);
}

// 매 프레임마다 호출
void Camera::FinalTick()
{
	// 플레이어가 화면의 중앙에 오도록 실제 좌표와 렌더링 좌표 차이값 설정
	diff.x = player->GetPos().x + (player->GetScale().x - resolution.x) * 0.5f;
	diff.y = player->GetPos().y + (player->GetScale().y - resolution.y) * 0.5f;
}