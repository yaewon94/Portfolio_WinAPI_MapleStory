#include "PCH.h"
#include "Background.h"
#include "Engine.h"

// ������
Background::Background() : GameObject(LAYER_TYPE::BACKGROUND)
{
}

// ���� ������
Background::Background(const Background& origin) : GameObject(origin)
{
}

// �Ҹ���
Background::~Background()
{
}

// �ʵ尪 ����
void Background::Set(Vec2<float> pos, Vec2<int> scale, Texture* texture)
{
	this->offset = pos;
	this->scale = scale;
	SetTexture(texture);
}