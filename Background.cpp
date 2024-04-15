#include "PCH.h"
#include "Background.h"
#include "Engine.h"

// ������
Background::Background() : GameObject(LAYER_TYPE::BACKGROUND), texture(nullptr)
{
}

// ���� ������
Background::Background(const Background& origin) : GameObject(origin), texture(origin.texture)
{
}

// �Ҹ���
Background::~Background()
{
	// Texture ��ü ���Ŵ� AssetManager ���
	texture = nullptr;
}

// �ʵ尪 ����
void Background::Set(Vec2 pos, Vec2 scale, Texture* texture)
{
	this->offset = pos;
	this->scale = scale;
	this->texture = texture;
}

// ������ (�� �����Ӹ��� ȣ��)
void Background::Render()
{
	assert(texture);

	// png �̹���
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