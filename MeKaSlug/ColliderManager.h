#pragma once
#include <map>
#include <list>
#include "Begin_DE.h"

// 역시 난 싱글톤으로 제작 - 메니저는 무조건 하나여야하는 것이
// 본인 철학ㅋㅋㅋㅋㅋㅋ
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
	// 콜리더 메니저는 콜리더를 개개인으로 관리하는 것이 아니라
	// 콜리더를 담는 그룹을 관리한다.
	class ColliderGroup : public Begin_DE
	{
	private:
		// 다른 (이어질 - 충돌처리할)그룹을 알아야한다.
		// 당연히 그 이터들도 자주 쓰일 것이기 때문에 미리 만든다.
		std::list<ColliderGroup*> m_ColliderGroup;
		std::list<ColliderGroup*>::iterator StartGroupIter;
		std::list<ColliderGroup*>::iterator EndGroupIter;

		// 다른 콜라이더와 현재그룹의 콜라이더를 포문을 두번 돌리기 위함
		// 실질적으로 해당 그룹이 가지고 있는 충돌체
		std::list<Collider*> m_ColliderList;
		std::list<Collider*>::iterator StartColliderIter;
		std::list<Collider*>::iterator EndColliderIter;
		std::list<Collider*>::iterator TheOhterStartColliderIter;
		std::list<Collider*>::iterator TheOhterEndColliderIter;

	public:
		// 어떤 [그] 다른그룹과의 충돌 처리 - 실질적인 충돌체의 충돌을 호출
		void TheOtherGroup_Collision(ColliderGroup* _pCol);

		// 다른 그룹(충돌 처리할 그릅)을 알아야한다.
		// 이 그룹에 어느 충돌체를 넣는다.
		// 그룹의 충돌 처리 -> 그룹의 충돌은 한 다른그룹과의 충돌처리를 함으로써 이루어진다.
		void Link(ColliderGroup* _Other);
		void Insert_Collider(Collider* _OtherCol);
		void Collision();
		void Release();

		// 충돌체를 보이게 -> 충돌체를 직접 관여하니까...
		void Obj_DebugRender();
		
		// 충돌체의 위치 보정 -> 샘은 충돌할 때만 하고 싶어하였으나
		// 그렇게는 못함 ㅠ.ㅠ
		void Calculate_Figure_Pos();

	public:
		ColliderGroup();
		~ColliderGroup();

	};

private:
	// 난 스테이트로 하나 더 싸야 한다 ;;
	
	std::map<std::wstring, std::map<std::wstring, ColliderGroup*>> m_map_Group;
	std::map<std::wstring, std::map<std::wstring, ColliderGroup*>>::iterator CollisionIter;
	std::map<std::wstring, std::map<std::wstring, ColliderGroup*>>::iterator CollisionFindIter;
	std::map<std::wstring, ColliderGroup*>::iterator GroupStartIter;
	std::map<std::wstring, ColliderGroup*>::iterator GroupEndIter;

private:
	ColliderGroup* Find_CreateGroup(const WCHAR* _StateName, const WCHAR* _Name);

	// 아니 이것만 왜 public으로 해야하냐... State에서 인식을 못한다.
	// 분명 friend로 베이스 스테이트 친구 걸어놨는데
public:
	bool Link(const WCHAR* _StateName, const WCHAR* _Left, const WCHAR* _Right);
private:
	void Insert_Collider(const WCHAR* _StateName, const WCHAR* _GroupName, Collider* _Other);
	void Insert_State(const WCHAR* _StateName);
	void Change_ColliderIter(const WCHAR* _StateName);
	void Collision();
	void Release();


	// 충돌체를 보이게 해준다.
	void Obj_DebugRender();

private:
	ColliderManager();
	~ColliderManager();
};

