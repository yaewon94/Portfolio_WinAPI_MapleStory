#pragma once
#include "GameObject.h"

class Texture;

// ��� ������Ʈ
// ������ ��� ������ �и�
class Background final : public GameObject
{
private:
	Texture* texture;

public:
	Background();
	Background(const Background& origin);
	~Background();
	virtual Background* Clone() override { return new Background(*this); }

	void Set(Vec2<float> pos, Vec2<int> scale, Texture* texture);

	virtual void Render() override;
};