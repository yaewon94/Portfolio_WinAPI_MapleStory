#include "PCH.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "GameObject.h"

// ������
CollisionManager::CollisionManager()
{
}

// �Ҹ���
CollisionManager::~CollisionManager()
{
	for (auto& layer : colliders)
	{
		// �ݶ��̴� ��ü�� Level���� ������Ʈ�� ������ �� ������
		layer.clear();
	}
}

// �� �����Ӹ��� ȣ��
void CollisionManager::FinalTick()
{
	// ��ϵ� �ݶ��̴� �浹üũ
	for (auto& layer : colliders)
	{
		for (auto collider : layer)
		{
			if(collider->GetOwner()->IsActive()) CollisionCheck(*collider);
		}
	}
}

// �ݶ��̴� ���
void CollisionManager::AddCollider(Collider& collider)
{
	colliders[(size_t)collider.GetOwner()->GetLayer()].push_back(&collider);
}

// �ݶ��̴� ����
void CollisionManager::RemoveCollider(Collider& collider)
{
	auto& vec = colliders[(size_t)collider.GetOwner()->GetLayer()];
	auto iter = vec.begin();

	for (; iter!=vec.end(); ++iter)
	{
		if (&collider == *iter)
		{
			vec.erase(iter);
			return;
		}
	}
}

// �浹 üũ
void CollisionManager::CollisionCheck(Collider& me)
{
	const size_t ArrSize = colliders.size();
	size_t myLayer = (size_t)me.GetOwner()->GetLayer();
	Collider *A, *B;
	bool isOverlapped;

	// �ڱ�� �ٸ� ���̾��� �ݶ��̴��� ������� üũ
	// �ڱ⺸�� ���� �ε����� ���̾�� �̹� �浹üũ�� �����Ƿ�, �ڽź��� ���� �ε����� ���̾ üũ
	for (size_t layer=myLayer+1; layer<ArrSize; ++layer)
	{
		for (auto other : colliders[layer])
		{
			// Ȱ��ȭ�� ������Ʈ�� üũ
			if (!other->GetOwner()->IsActive()) continue;

			// X�� ��ħ ���� üũ
			if (me.GetPos().x > other->GetPos().x)
			{
				A = &me;
				B = other;
			}
			else
			{
				A = other;
				B = &me;
			}
			
			if (A->GetPos().x + A->GetScale().x - B->GetPos().x <= A->GetScale().x + B->GetScale().x)
			{
				// Y�� ��ħ ���� üũ
				if (me.GetPos().y > other->GetPos().y)
				{
					A = &me;
					B = other;
				}
				else
				{
					A = other;
					B = &me;
				}

				if (A->GetPos().y + A->GetScale().y - B->GetPos().y <= A->GetScale().y + B->GetScale().y) isOverlapped = true;
				else isOverlapped = false;
			}
			else
			{
				isOverlapped = false;
			}

			// ���� ������ �浹 ���ο� ���� �浹 �̺�Ʈ ȣ��
			ExecuteCollisionEvent(me, *other, isOverlapped);
		}
	}
}

// �浹 �̺�Ʈ ȣ��
void CollisionManager::ExecuteCollisionEvent(Collider& a, Collider& b, bool isOverlapped)
{
	GameObject* obj1 = a.GetOwner();
	GameObject* obj2 = b.GetOwner();
	UINT id1, id2;

	// ������Ʈ ID�� ���� ������ �浹 ���� ������
	if (obj1->GetID() > obj2->GetID())
	{
		id1 = obj1->GetID();
		id2 = obj2->GetID();
	}
	else
	{
		id1 = obj2->GetID();
		id2 = obj1->GetID();
	}

	auto pair = stateMap.find(std::pair{ id1, id2 });
	if (pair == stateMap.end())
	{
		stateMap.insert(make_pair(std::pair{ id1, id2 }, false));
		--pair;
	}


	// �浹 �̺�Ʈ ȣ��
	if (isOverlapped)
	{
		// ���� �����ӿ��� �浹���� ���
		if(pair->second)
		{
			obj1->OnCollisionStay(*obj2);
			obj2->OnCollisionStay(*obj1);
		}
		// �浹���� ���� ���
		else
		{
			obj1->OnCollisionEnter(*obj2);
			obj2->OnCollisionEnter(*obj1);
		}
	}
	else
	{
		// ���� �����ӿ� �浹�� ���
		if (pair->second)
		{
			obj1->OnCollisionExit(*obj2);
			obj2->OnCollisionExit(*obj1);
		}
	}

	// ���� ������ �浹 ���� �ݿ�
	pair->second = isOverlapped;
}