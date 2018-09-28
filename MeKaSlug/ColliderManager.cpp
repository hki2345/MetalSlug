#include "stdafx.h"
#include "Collider.h"
#include "ColliderManager.h"

ColliderManager::ColliderGroup::ColliderGroup()
{

}
ColliderManager::ColliderGroup::~ColliderGroup()
{
}

void ColliderManager::ColliderGroup::Insert_Collider(Collider* _OtherCol)
{
	KAssert(nullptr == _OtherCol);
	m_ColliderList.push_back(_OtherCol);
}

// 이어준다는 것은 그 그룹을 다른 그룹을 담고있는 리스트에 넣는 것으로도 해석된다.
void ColliderManager::ColliderGroup::Link(ColliderGroup* _Other)
{
	KAssert(nullptr == _Other);
	if(nullptr == _Other)
	{
		return;
	}

	StartGroupIter = m_ColliderGroup.begin();
	EndGroupIter = m_ColliderGroup.end();

	// 자신을 넣지는 못한다.
	for (; StartGroupIter != EndGroupIter; StartGroupIter++)
	{
		KAssert(Name() == (*StartGroupIter)->Name());
		if(Name() == (*StartGroupIter)->Name())
		{
			return;
		}
	}

	m_ColliderGroup.push_back(_Other);
}

// 그룹이 가진 다른 그룹과 충돌
void ColliderManager::ColliderGroup::Collision()
{
	// 역시 그룹을 하나도 가지고 있지 않으면 충돌 검사를 할수 없겠다.
	if (0 >= m_ColliderGroup.size())
	{ return; }

	StartGroupIter = m_ColliderGroup.begin();
	EndGroupIter = m_ColliderGroup.end();

	for (; StartGroupIter != EndGroupIter; StartGroupIter++)
	{
		TheOtherGroup_Collision(*StartGroupIter);
	}
}

// 실제 충돌체를 충돌 처리한다.
void ColliderManager::ColliderGroup::TheOtherGroup_Collision(ColliderGroup* _pCol)
{
	// 나의 위치 보정
	Calculate_Figure_Pos();

	// 어느 한쪽 중 콜리더(충돌체)가 없다면 충돌 처리를 할 수 없다. ㅇㅇ
	if((m_ColliderList.size() == 0 )|| (_pCol->m_ColliderList.size() == 0))
	{ return; }

	// 짝꿍이 없으면 역시 이것도 실행 안돼
	// 짝궁이 되는 그녀석도 위치보정 ㅎㄷㄷ;;
	_pCol->Calculate_Figure_Pos();

	// 내그룹간에 충돌이 아니라면
	if (this != _pCol)
	{
		StartColliderIter = m_ColliderList.begin();
		EndColliderIter = m_ColliderList.end();

		for (; StartColliderIter != EndColliderIter; StartColliderIter++)
		{
			TheOhterStartColliderIter = _pCol->m_ColliderList.begin();
			TheOhterEndColliderIter = _pCol->m_ColliderList.end();

			for (; TheOhterStartColliderIter != TheOhterEndColliderIter ; TheOhterStartColliderIter++)
			{
				(*StartColliderIter)->Collision(*TheOhterStartColliderIter);
			}
		}
	}

	// 내그룹이란 그룹 안에서 충돌체끼리 충돌하는 경우를 말함
	// 그게 이 경우
	else
	{

	}
}


void ColliderManager::ColliderGroup::Calculate_Figure_Pos()
{
	StartColliderIter = m_ColliderList.begin();
	EndColliderIter = m_ColliderList.end();

	for (; StartColliderIter != EndColliderIter; StartColliderIter++)
	{
		(*StartColliderIter)->Calculate_Figure_Pos();
	}
}

void  ColliderManager::ColliderGroup::Obj_DebugRender()
{
	StartColliderIter = m_ColliderList.begin();
	EndColliderIter = m_ColliderList.end();

	for (; StartColliderIter != EndColliderIter; StartColliderIter++)
	{
		(*StartColliderIter)->Obj_Debug_Render();
	}
}

void  ColliderManager::ColliderGroup::Release()
{
	StartColliderIter = m_ColliderList.begin();
	EndColliderIter = m_ColliderList.end();

	for (; StartColliderIter != EndColliderIter; )
	{
		(*StartColliderIter)->Release();

		if ((*StartColliderIter)->Death())
		{
			StartColliderIter = m_ColliderList.erase(StartColliderIter);
		}
		else
		{
			StartColliderIter++;
		}
	}
}





/**************************** ColliderManager ******************************/

// 메니저에서 그룹을 찾는데 없으면 그 그룹을 만들어주기까진한다.
ColliderManager::ColliderGroup* ColliderManager::Find_CreateGroup(const WCHAR* _StateName, const WCHAR* _GroupName)
{
	CollisionFindIter = m_map_Group.find(_StateName);
	std::map<std::wstring, ColliderGroup*>::iterator FindIter = CollisionFindIter->second.find(_GroupName);

	// 무조건 만들곗다는 의지
	ColliderGroup* NewGroup = nullptr;

	// 없으면 만들라
	if (CollisionFindIter->second.end() == FindIter)
	{
		NewGroup = new ColliderGroup();
		NewGroup->Name(_GroupName);
		CollisionFindIter->second.insert(std::map<std::wstring, ColliderGroup*>::value_type(_GroupName, NewGroup));
		return NewGroup;
	}

	NewGroup = FindIter->second;
	return NewGroup;
}

void ColliderManager::Insert_State(const WCHAR* _StateName)
{
	CollisionFindIter = m_map_Group.find(_StateName);
	std::map<std::wstring, ColliderGroup*> NewStateColliderGroup = std::map<std::wstring, ColliderGroup*>();

	// 없으면 -> 넣는다.
	if (CollisionFindIter == m_map_Group.end())
	{
		// 일단 키만 만들어 놓는다? ㅇㅇ
		m_map_Group.insert
		(std::map<std::wstring, std::map<std::wstring, ColliderGroup*>>::value_type(_StateName, NewStateColliderGroup));
	}
}

//  좌우에 있는 그룹(이름을 가진)을 이어준다 -> 충돌할 수 있도록 한다.
bool ColliderManager::Link(const WCHAR* _StateName, const WCHAR* _Left, const WCHAR* _Right)
{
	ColliderGroup* LeftGroup = Find_CreateGroup(_StateName, _Left);
	ColliderGroup* RightGroup = Find_CreateGroup(_StateName, _Right);

	KAssert(nullptr == LeftGroup || nullptr == RightGroup);

	// 정식 그거
	if (nullptr == LeftGroup || nullptr == RightGroup)
	{
		return false;
	}

	// 왼쪽 기준으로 이어붙힌다. -> 오른쪽에선 왼쪽을 모른다.
	LeftGroup->Link(RightGroup);
	return true;
}

// 충돌체를 넣는다.
void ColliderManager::Insert_Collider(const WCHAR* _StateName, const WCHAR* _GroupName, Collider* _Other)
{
	ColliderGroup* NewGroup = Find_CreateGroup(_StateName, _GroupName);
	KAssert(nullptr == NewGroup);
	NewGroup->Insert_Collider(_Other);
}

void ColliderManager::Change_ColliderIter(const WCHAR* _StateName)
{
	// 찾는다 -> 굳이 뭐 할 필요 없이 방어코드만 쳐놓고 아무 것도 안해도 된다.
	// 이터는 그 것만 가리켜도 제 할일을 하는 것이다.
	CollisionIter = m_map_Group.find(_StateName);

	if (CollisionIter == m_map_Group.end())
	{
		KAssert(true);
	}
}

void ColliderManager::Collision()
{
	GroupStartIter = CollisionIter->second.begin();
	GroupEndIter = CollisionIter->second.end();

	for (; GroupStartIter != GroupEndIter; GroupStartIter++)
	{
		GroupStartIter->second->Collision();
	}
}

void ColliderManager::Release()
{
	GroupStartIter = CollisionIter->second.begin();
	GroupEndIter = CollisionIter->second.end();

	for (; GroupStartIter != GroupEndIter; GroupStartIter++)
	{
		GroupStartIter->second->Release();
	}
}

void ColliderManager::Obj_DebugRender()
{
	GroupStartIter = CollisionIter->second.begin();
	GroupEndIter = CollisionIter->second.end();

	for (; GroupStartIter != GroupEndIter; GroupStartIter++)
	{
		GroupStartIter->second->Obj_DebugRender();
	}
}






ColliderManager::ColliderManager()
{
}


ColliderManager::~ColliderManager()
{
	std::map<std::wstring, std::map<std::wstring, ColliderGroup*>>::iterator Map_GroupStartIter = m_map_Group.begin();
	std::map<std::wstring, std::map<std::wstring, ColliderGroup*>>::iterator Map_GroupEndIter = m_map_Group.end();
	
	for (; Map_GroupStartIter != Map_GroupEndIter; Map_GroupStartIter++)
	{
		std::map<std::wstring, ColliderGroup* > ::iterator t_GroupStartIter = Map_GroupStartIter->second.begin();
		std::map<std::wstring, ColliderGroup* > ::iterator t_GroupEndIter = Map_GroupStartIter->second.end();

		for (; t_GroupStartIter != t_GroupEndIter; t_GroupStartIter++)
		{
			NEW_DELETE(t_GroupStartIter->second);
		}
	}
}
