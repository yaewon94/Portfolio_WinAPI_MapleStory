#pragma once
#include "Entity.h"

class Level;
class Texture;

// ∏  ≈¨∑°Ω∫
class Map final : public Entity
{
	friend class Level;
	NO_CSTR_COPY_ASSIGN(Map);

private:
	wstring name;
	Vec2<float> pos;		// ∏  ¡¬«• (¡ﬂæ” ±‚¡ÿ)
	Vec2<int> scale;		// ∏  ≈©±‚
	Texture* background;	// πË∞Ê ¿ÃπÃ¡ˆ

public:
	Map(const wstring& name, Vec2<float> pos, Vec2<int> scale, Texture& background);
	~Map();

	Vec2<float> GetPos() { return pos; }
	Vec2<int> GetScale() { return scale; }

	void Enter();
};