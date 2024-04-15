#include "PCH.h"
#include "Camera.h"
#include "Engine.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "Map.h"

// 소스파일 전역변수
static float mapHalfScaleX = 0.f;
static float mapHalfScaleY = 0.f;

// 생성자
Camera::Camera()
	: resolution(Engine::GetInstance().GetResolution())
	, player(nullptr), currentMap(nullptr)
{
}

// 소멸자
Camera::~Camera()
{
	player = nullptr;
	currentMap = nullptr;
}

// 초기화
void Camera::Init()
{
	player = LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER);
}

// 매 프레임마다 호출
void Camera::FinalTick()
{
	float prevDiffX = diff.x;
	float prevDiffY = diff.y;

	// 플레이어가 화면의 중앙에 오도록 실제 좌표와 렌더링 좌표 차이값 설정
	diff.x = player->GetPos().x + (player->GetScale().x - resolution.x) * 0.5f;
	diff.y = player->GetPos().y + (player->GetScale().y - resolution.y) * 0.5f;

	// 차이값이 맵 렌더링 범위를 벗어나는지 확인
	if (diff.x < currentMap->GetPos().x - mapHalfScaleX
		|| diff.x > currentMap->GetPos().x + mapHalfScaleX - resolution.x) diff.x = prevDiffX;
	if (diff.y < currentMap->GetPos().y - mapHalfScaleY
		|| diff.y > currentMap->GetPos().y + mapHalfScaleY - resolution.y) diff.y = prevDiffY;
}

// 현재 맵 변경
void Camera::SetCurrentMap(Map* map)
{
	currentMap = map;
	mapHalfScaleX = currentMap->GetScale().x * 0.5f;
	mapHalfScaleY = currentMap->GetScale().y * 0.5f;

	// diff를 맵의 범위에 맞춰준다
	float left, right, top, bottom;
	if (diff.x < (left = currentMap->GetPos().x - mapHalfScaleX)) diff.x = left;
	else if (diff.x > (right = currentMap->GetPos().x + mapHalfScaleX - resolution.x)) diff.x = right;
	if (diff.y < (top = currentMap->GetPos().y - mapHalfScaleY)) diff.y = top;
	else if (diff.y > (bottom = currentMap->GetPos().y + mapHalfScaleY - resolution.y)) diff.y = bottom;
}