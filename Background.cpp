#include "PCH.h"
#include "Background.h"
#include "Engine.h"

// 생성자
Background::Background() : GameObject(LAYER_TYPE::BACKGROUND)
{
}

// 복사 생성자
Background::Background(const Background& origin) : GameObject(origin)
{
}

// 소멸자
Background::~Background()
{
}

// 필드값 설정
void Background::Set(Vec2<float> pos, Vec2<int> scale, Texture* texture)
{
	this->offset = pos;
	this->scale = scale;
	SetTexture(texture);
}