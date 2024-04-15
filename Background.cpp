#include "PCH.h"
#include "Background.h"
#include "Engine.h"

// 생성자
Background::Background() : GameObject(LAYER_TYPE::BACKGROUND), texture(nullptr)
{
}

// 복사 생성자
Background::Background(const Background& origin) : GameObject(origin), texture(origin.texture)
{
}

// 소멸자
Background::~Background()
{
	// Texture 객체 제거는 AssetManager 담당
	texture = nullptr;
}

// 필드값 설정
void Background::Set(Vec2 pos, Vec2 scale, Texture* texture)
{
	this->offset = pos;
	this->scale = scale;
	this->texture = texture;
}

// 렌더링 (매 프레임마다 호출)
void Background::Render()
{
	assert(texture);

	// png 이미지
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(Engine::GetInstance().GetSubDC()
		, (int)(GetRenderPos().x - scale.x * 0.5f), (int)(GetRenderPos().y - scale.y * 0.5f)
		, texture->GetWidth(), texture->GetHeight()
		, texture->GetDC()
		, 0, 0
		, texture->GetWidth(), texture->GetHeight()
		, bf);
}