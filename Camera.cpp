#include "PCH.h"
#include "Camera.h"
#include "Engine.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "Map.h"

// 소스파일 전역변수
static float mapLeftLimit, mapRightLimit, mapTopLimit, mapBottomLimit;

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

	// diff를 현재 맵의 범위에 맞춤 (Init이 SetCurrentMap 첫번째 호출보다 나중에 호출됨)
	AdjustDiffToMap();
}

// 매 프레임마다 호출
void Camera::FinalTick()
{
	float prevDiffX = diff.x;
	float prevDiffY = diff.y;

	// 플레이어가 화면의 중앙에 오도록 실제 좌표와 렌더링 좌표 차이값 설정
	diff.x = player->GetRealPos().x + (player->GetScale().x - resolution.x) * 0.5f;
	diff.y = player->GetRealPos().y + (player->GetScale().y - resolution.y) * 0.5f;

	// 차이값이 맵 렌더링 범위를 벗어나는지 확인
	if (diff.y < mapTopLimit || diff.y > mapBottomLimit) diff.y = prevDiffY;
	if (diff.x < mapLeftLimit || diff.x > mapRightLimit) diff.x = prevDiffX;
}

// 현재 맵 변경
void Camera::SetCurrentMap(Map* map)
{
	currentMap = map;
	AdjustDiffToMap();
}

// diff를 맵의 범위에 맞춘다 (맵 밖이 렌더링되지 않도록)
void Camera::AdjustDiffToMap()
{
	float mapHalfScaleX = currentMap->GetScale().x * 0.5f;
	float mapHalfScaleY = currentMap->GetScale().y * 0.5f;

	// 플레이어가 화면의 중앙에 오도록 실제 좌표와 렌더링 좌표 차이값 설정
	if(player != nullptr)
	{
		diff.x = player->GetRealPos().x + (player->GetScale().x - resolution.x) * 0.5f;
		diff.y = player->GetRealPos().y + (player->GetScale().y - resolution.y) * 0.5f;
	}

	// x축
	if (diff.x < (mapLeftLimit = currentMap->GetPos().x - mapHalfScaleX)) diff.x = mapLeftLimit;
	else if (diff.x > (mapRightLimit = currentMap->GetPos().x + mapHalfScaleX - resolution.x)) diff.x = mapRightLimit;

	// y축
	if (diff.y < (mapTopLimit = currentMap->GetPos().y - mapHalfScaleY)) diff.y = mapTopLimit;
	else if (diff.y > (mapBottomLimit = currentMap->GetPos().y + mapHalfScaleY - resolution.y)) diff.y = mapBottomLimit;
}