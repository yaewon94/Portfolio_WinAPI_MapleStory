#pragma once
#include "Entity.h"

class Level;
class Texture;

class GameObject;

// �� Ŭ����
class Map final : public Entity
{
	friend class MapManager;
	NO_CSTR_COPY_ASSIGN(Map);

private:
	wstring name;
	Vec2<float> pos;		// �� ��ǥ (�߾� ����)
	Vec2<int> scale;		// �� ũ��
	Texture* background;	// ��� �̹���
	vector<GameObject*> managedObjs;	// ���� ������ ������Ʈ (�� �����, ��Ȱ��ȭ��ų ������Ʈ ��)

	const Vec2<float> DefaultPlayerPos;	// ��Ż �̵��� ������ ������� �ʿ� ���� ��, �÷��̾� ������Ʈ�� ��ġ�� ��ǥ

private:
	Map(const wstring& name, Vec2<float> pos, Vec2<int> scale, Texture& background, Vec2<float> defaultPlayerPos);
	~Map();

	void Enter();
	void Exit();

public:
	Vec2<float> GetPos() { return pos; }
	Vec2<int> GetScale() { return scale; }
};