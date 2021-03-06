#pragma once
#include <map>
#include <list>
#include "Begin_DE.h"

// 蝕獣 貝 縮越宕生稽 薦拙 - 五艦煽澗 巷繕闇 馬蟹食醤馬澗 依戚
// 沙昔 旦俳せせせせせせ
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
	// 紬軒希 五艦煽澗 紬軒希研 鯵鯵昔生稽 淫軒馬澗 依戚 焼艦虞
	// 紬軒希研 眼澗 益血聖 淫軒廃陥.
	class ColliderGroup : public Begin_DE
	{
	private:
		// 陥献 (戚嬢霜 - 中宜坦軒拝)益血聖 硝焼醤廃陥.
		// 雁尻備 益 戚斗級亀 切爽 床析 依戚奄 凶庚拭 耕軒 幻窮陥.
		std::list<ColliderGroup*> m_ColliderGroup;
		std::list<ColliderGroup*>::iterator StartGroupIter;
		std::list<ColliderGroup*>::iterator EndGroupIter;

		// 陥献 紬虞戚希人 薄仙益血税 紬虞戚希研 匂庚聖 砧腰 宜軒奄 是敗
		// 叔霜旋生稽 背雁 益血戚 亜走壱 赤澗 中宜端
		std::list<Collider*> m_ColliderList;
		std::list<Collider*>::iterator StartColliderIter;
		std::list<Collider*>::iterator EndColliderIter;
		std::list<Collider*>::iterator TheOhterStartColliderIter;
		std::list<Collider*>::iterator TheOhterEndColliderIter;

	public:
		// 嬢恐 [益] 陥献益血引税 中宜 坦軒 - 叔霜旋昔 中宜端税 中宜聖 硲窒
		void TheOtherGroup_Collision(ColliderGroup* _pCol);

		// 陥献 益血(中宜 坦軒拝 益絹)聖 硝焼醤廃陥.
		// 戚 益血拭 嬢汗 中宜端研 隔澗陥.
		// 益血税 中宜 坦軒 -> 益血税 中宜精 廃 陥献益血引税 中宜坦軒研 敗生稽潤 戚欠嬢遭陥.
		void Link(ColliderGroup* _Other);
		void Insert_Collider(Collider* _OtherCol);
		void Collision();
		void Release();

		// 中宜端研 左戚惟 -> 中宜端研 送羨 淫食馬艦猿...
		void Obj_DebugRender();
		
		// 中宜端税 是帖 左舛 -> 児精 中宜拝 凶幻 馬壱 粛嬢馬心生蟹
		// 益係惟澗 公敗 ば.ば
		void Calculate_Figure_Pos();

	public:
		ColliderGroup();
		~ColliderGroup();

	};

private:
	// 貝 什砺戚闘稽 馬蟹 希 塾醤 廃陥 ;;
	
	std::map<std::wstring, std::map<std::wstring, ColliderGroup*>> m_map_Group;
	std::map<std::wstring, std::map<std::wstring, ColliderGroup*>>::iterator CollisionIter;
	std::map<std::wstring, std::map<std::wstring, ColliderGroup*>>::iterator CollisionFindIter;
	std::map<std::wstring, ColliderGroup*>::iterator GroupStartIter;
	std::map<std::wstring, ColliderGroup*>::iterator GroupEndIter;

private:
	ColliderGroup* Find_CreateGroup(const WCHAR* _StateName, const WCHAR* _Name);

	// 焼艦 戚依幻 訊 public生稽 背醤馬劃... State拭辞 昔縦聖 公廃陥.
	// 歳誤 friend稽 今戚什 什砺戚闘 庁姥 杏嬢鎌澗汽
public:
	bool Link(const WCHAR* _StateName, const WCHAR* _Left, const WCHAR* _Right);
private:
	void Insert_Collider(const WCHAR* _StateName, const WCHAR* _GroupName, Collider* _Other);
	void Insert_State(const WCHAR* _StateName);
	void Change_ColliderIter(const WCHAR* _StateName);
	void Collision();
	void Release();


	// 中宜端研 左戚惟 背層陥.
	void Obj_DebugRender();

private:
	ColliderManager();
	~ColliderManager();
};

