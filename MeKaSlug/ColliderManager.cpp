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

// �̾��شٴ� ���� �� �׷��� �ٸ� �׷��� ����ִ� ����Ʈ�� �ִ� �����ε� �ؼ��ȴ�.
void ColliderManager::ColliderGroup::Link(ColliderGroup* _Other)
{
	KAssert(nullptr == _Other);
	if(nullptr == _Other)
	{
		return;
	}

	StartGroupIter = m_ColliderGroup.begin();
	EndGroupIter = m_ColliderGroup.end();

	// �ڽ��� ������ ���Ѵ�.
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

// �׷��� ���� �ٸ� �׷�� �浹
void ColliderManager::ColliderGroup::Collision()
{
	// ���� �׷��� �ϳ��� ������ ���� ������ �浹 �˻縦 �Ҽ� ���ڴ�.
	if (0 >= m_ColliderGroup.size())
	{ return; }

	StartGroupIter = m_ColliderGroup.begin();
	EndGroupIter = m_ColliderGroup.end();

	for (; StartGroupIter != EndGroupIter; StartGroupIter++)
	{
		TheOtherGroup_Collision(*StartGroupIter);
	}
}

// ���� �浹ü�� �浹 ó���Ѵ�.
void ColliderManager::ColliderGroup::TheOtherGroup_Collision(ColliderGroup* _pCol)
{
	// ���� ��ġ ����
	Calculate_Figure_Pos();

	// ��� ���� �� �ݸ���(�浹ü)�� ���ٸ� �浹 ó���� �� �� ����. ����
	if((m_ColliderList.size() == 0 )|| (_pCol->m_ColliderList.size() == 0))
	{ return; }

	// ¦���� ������ ���� �̰͵� ���� �ȵ�
	// ¦���� �Ǵ� �׳༮�� ��ġ���� ������;;
	_pCol->Calculate_Figure_Pos();

	// ���׷찣�� �浹�� �ƴ϶��
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

	// ���׷��̶� �׷� �ȿ��� �浹ü���� �浹�ϴ� ��츦 ����
	// �װ� �� ���
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

// �޴������� �׷��� ã�µ� ������ �� �׷��� ������ֱ�����Ѵ�.
ColliderManager::ColliderGroup* ColliderManager::Find_CreateGroup(const WCHAR* _StateName, const WCHAR* _GroupName)
{
	CollisionFindIter = m_map_Group.find(_StateName);
	std::map<std::wstring, ColliderGroup*>::iterator FindIter = CollisionFindIter->second.find(_GroupName);

	// ������ �����ٴ� ����
	ColliderGroup* NewGroup = nullptr;

	// ������ �����
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

	// ������ -> �ִ´�.
	if (CollisionFindIter == m_map_Group.end())
	{
		// �ϴ� Ű�� ����� ���´�? ����
		m_map_Group.insert
		(std::map<std::wstring, std::map<std::wstring, ColliderGroup*>>::value_type(_StateName, NewStateColliderGroup));
	}
}

//  �¿쿡 �ִ� �׷�(�̸��� ����)�� �̾��ش� -> �浹�� �� �ֵ��� �Ѵ�.
bool ColliderManager::Link(const WCHAR* _StateName, const WCHAR* _Left, const WCHAR* _Right)
{
	ColliderGroup* LeftGroup = Find_CreateGroup(_StateName, _Left);
	ColliderGroup* RightGroup = Find_CreateGroup(_StateName, _Right);

	KAssert(nullptr == LeftGroup || nullptr == RightGroup);

	// ���� �װ�
	if (nullptr == LeftGroup || nullptr == RightGroup)
	{
		return false;
	}

	// ���� �������� �̾������. -> �����ʿ��� ������ �𸥴�.
	LeftGroup->Link(RightGroup);
	return true;
}

// �浹ü�� �ִ´�.
void ColliderManager::Insert_Collider(const WCHAR* _StateName, const WCHAR* _GroupName, Collider* _Other)
{
	ColliderGroup* NewGroup = Find_CreateGroup(_StateName, _GroupName);
	KAssert(nullptr == NewGroup);
	NewGroup->Insert_Collider(_Other);
}

void ColliderManager::Change_ColliderIter(const WCHAR* _StateName)
{
	// ã�´� -> ���� �� �� �ʿ� ���� ����ڵ常 �ĳ��� �ƹ� �͵� ���ص� �ȴ�.
	// ���ʹ� �� �͸� �����ѵ� �� ������ �ϴ� ���̴�.
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
