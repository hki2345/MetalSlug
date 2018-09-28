#pragma once
#include <map>
#include <list>
#include "Begin_DE.h"

// ���� �� �̱������� ���� - �޴����� ������ �ϳ������ϴ� ����
// ���� ö�Ф�����������
class ColliderManager
{
public:
	friend class Core;
	friend class Collider;
	friend class BaseState;

public:
	static ColliderManager& Inst()
	{
		static ColliderManager ThisColliderMgr = ColliderManager();
		return ThisColliderMgr;
	}


private:
	// �ݸ��� �޴����� �ݸ����� ���������� �����ϴ� ���� �ƴ϶�
	// �ݸ����� ��� �׷��� �����Ѵ�.
	class ColliderGroup : public Begin_DE
	{
	private:
		// �ٸ� (�̾��� - �浹ó����)�׷��� �˾ƾ��Ѵ�.
		// �翬�� �� ���͵鵵 ���� ���� ���̱� ������ �̸� �����.
		std::list<ColliderGroup*> m_ColliderGroup;
		std::list<ColliderGroup*>::iterator StartGroupIter;
		std::list<ColliderGroup*>::iterator EndGroupIter;

		// �ٸ� �ݶ��̴��� ����׷��� �ݶ��̴��� ������ �ι� ������ ����
		// ���������� �ش� �׷��� ������ �ִ� �浹ü
		std::list<Collider*> m_ColliderList;
		std::list<Collider*>::iterator StartColliderIter;
		std::list<Collider*>::iterator EndColliderIter;
		std::list<Collider*>::iterator TheOhterStartColliderIter;
		std::list<Collider*>::iterator TheOhterEndColliderIter;

	public:
		// � [��] �ٸ��׷���� �浹 ó�� - �������� �浹ü�� �浹�� ȣ��
		void TheOtherGroup_Collision(ColliderGroup* _pCol);

		// �ٸ� �׷�(�浹 ó���� �׸�)�� �˾ƾ��Ѵ�.
		// �� �׷쿡 ��� �浹ü�� �ִ´�.
		// �׷��� �浹 ó�� -> �׷��� �浹�� �� �ٸ��׷���� �浹ó���� �����ν� �̷������.
		void Link(ColliderGroup* _Other);
		void Insert_Collider(Collider* _OtherCol);
		void Collision();
		void Release();

		// �浹ü�� ���̰� -> �浹ü�� ���� �����ϴϱ�...
		void Obj_DebugRender();
		
		// �浹ü�� ��ġ ���� -> ���� �浹�� ���� �ϰ� �;��Ͽ�����
		// �׷��Դ� ���� ��.��
		void Calculate_Figure_Pos();

	public:
		ColliderGroup();
		~ColliderGroup();

	};

private:
	// �� ������Ʈ�� �ϳ� �� �ξ� �Ѵ� ;;
	
	std::map<std::wstring, std::map<std::wstring, ColliderGroup*>> m_map_Group;
	std::map<std::wstring, std::map<std::wstring, ColliderGroup*>>::iterator CollisionIter;
	std::map<std::wstring, std::map<std::wstring, ColliderGroup*>>::iterator CollisionFindIter;
	std::map<std::wstring, ColliderGroup*>::iterator GroupStartIter;
	std::map<std::wstring, ColliderGroup*>::iterator GroupEndIter;

private:
	ColliderGroup* Find_CreateGroup(const WCHAR* _StateName, const WCHAR* _Name);

	// �ƴ� �̰͸� �� public���� �ؾ��ϳ�... State���� �ν��� ���Ѵ�.
	// �и� friend�� ���̽� ������Ʈ ģ�� �ɾ���µ�
public:
	bool Link(const WCHAR* _StateName, const WCHAR* _Left, const WCHAR* _Right);
private:
	void Insert_Collider(const WCHAR* _StateName, const WCHAR* _GroupName, Collider* _Other);
	void Insert_State(const WCHAR* _StateName);
	void Change_ColliderIter(const WCHAR* _StateName);
	void Collision();
	void Release();


	// �浹ü�� ���̰� ���ش�.
	void Obj_DebugRender();

private:
	ColliderManager();
	~ColliderManager();
};

