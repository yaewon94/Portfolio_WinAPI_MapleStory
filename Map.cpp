#include "PCH.h"
#include "Map.h"
#include "Background.h"
#include "Camera.h"
#include "LevelManager.h"

// 생성자
Map::Map(const wstring& name, Vec2<float> pos, Vec2<int> scale, Texture& background)
	: name(name), pos(pos), scale(scale), background(&background)
{
}

// 소멸자
Map::~Map()
{
	// Texture 객체 제거는 AssetManager가 담당함
	background = nullptr;
}

// 맵 진입
void Map::Enter()
{
	// 메인카메라에 현재 맵 정보 설정
	LevelManager::GetInstance().GetMainCamera()->SetCurrentMap(this);
	
	// 배경 오브젝트 값 설정
	Background* obj_background = (Background*)LevelManager::GetInstance().FindObject(LAYER_TYPE::BACKGROUND);
	obj_background->Set(pos, scale, background);
}