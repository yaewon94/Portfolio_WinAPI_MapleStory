#include "PCH.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "GameObject.h"

// 생성자
CollisionManager::CollisionManager()
{
}

// 소멸자
CollisionManager::~CollisionManager()
{
	for (auto& layer : colliders)
	{
		// 콜라이더 객체는 Level에서 오브젝트가 삭제될 때 삭제됨
		layer.clear();
	}
}

// 매 프레임마다 호출
void CollisionManager::FinalTick()
{
	// 등록된 콜라이더 충돌체크
	for (auto& layer : colliders)
	{
		for (auto collider : layer)
		{
			if(collider->GetOwner()->IsActive()) CollisionCheck(*collider);
		}
	}
}

// 콜라이더 등록
void CollisionManager::AddCollider(Collider& collider)
{
	colliders[(size_t)collider.GetOwner()->GetLayer()].push_back(&collider);
}

// 콜라이더 삭제
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

// 충돌 체크
void CollisionManager::CollisionCheck(Collider& me)
{
	const size_t ArrSize = colliders.size();
	size_t myLayer = (size_t)me.GetOwner()->GetLayer();
	float diffX, diffY;
	bool isOverlapped;

	// 자기와 다른 레이어의 콜라이더를 대상으로 체크
	// 자기보다 낮은 인덱스의 레이어는 이미 충돌체크를 했으므로, 자신보다 높은 인덱스의 레이어만 체크
	for (size_t layer=myLayer+1; layer<ArrSize; ++layer)
	{
		for (auto other : colliders[layer])
		{
			// 활성화된 오브젝트만 체크
			if (!other->GetOwner()->IsActive()) continue;

			// X축 겹침 여부 체크
			diffX = me.GetPos().x - other->GetPos().x;
			if (diffX < 0) diffX = -diffX;

			if(diffX <= (me.GetScale().x + other->GetScale().x) * 0.5f)
			{
				// Y축 겹침 여부 체크
				diffY = me.GetPos().y - other->GetPos().y;
				if (diffY < 0) diffY = -diffY;

				if (diffY <= (me.GetScale().y + other->GetScale().y) * 0.5f) isOverlapped = true;
				else isOverlapped = false;
			}
			else
			{
				isOverlapped = false;
			}

			// 이전 프레임 충돌 여부에 따라 충돌 이벤트 호출
			ExecuteCollisionEvent(me, *other, isOverlapped);
		}
	}
}

// 충돌 이벤트 호출
void CollisionManager::ExecuteCollisionEvent(Collider& a, Collider& b, bool isOverlapped)
{
	GameObject* obj1 = a.GetOwner();
	GameObject* obj2 = b.GetOwner();
	UINT id1, id2;

	// 오브젝트 ID로 이전 프레임 충돌 여부 얻어오기
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


	// 충돌 이벤트 호출
	if (isOverlapped)
	{
		// 이전 프레임에도 충돌했을 경우
		if(pair->second)
		{
			obj1->OnCollisionStay(*obj2);
			obj2->OnCollisionStay(*obj1);
		}
		// 충돌하지 않은 경우
		else
		{
			obj1->OnCollisionEnter(*obj2);
			obj2->OnCollisionEnter(*obj1);
		}
	}
	else
	{
		// 이전 프레임에 충돌한 경우
		if (pair->second)
		{
			obj1->OnCollisionExit(*obj2);
			obj2->OnCollisionExit(*obj1);
		}
	}

	// 현재 프레임 충돌 여부 반영
	pair->second = isOverlapped;
}