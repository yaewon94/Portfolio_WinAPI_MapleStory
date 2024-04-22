#include "PCH.h"
#include "Skill.h"
#include "Animation.h"

// ������
Skill::Skill(const wstring& name) : name(name)
{
}

// �Ҹ���
Skill::~Skill()
{
	for (auto& pair : animMap)
	{
		if (pair.second != nullptr)
		{
			// ERROR : �߸�����
			// ���⼭ �����ߵǴµ�, ��ų������Ʈ�� ��ų�� �Ҵ�� ���¸�
			// ��ų������Ʈ �Ҹ���->�ִϸ����� ������Ʈ �Ҹ���->�ִϸ��̼� �Ҹ��� ȣ�� �Ǽ� ������
			delete pair.second;
			pair.second = nullptr;
		}
	}

	animMap.clear();
}

// ��ų������Ʈ ������� �ݹ�
void Skill::OnDisappear(GameObject* obj)
{
	if(on_disappear != nullptr) on_disappear(obj);
}