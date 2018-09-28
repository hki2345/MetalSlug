#pragma once
#include "BaseEnemy.h"

class MapData_Creator : public BaseEnemy
{
public:
	class EnemyData
	{
		// 인트를 2배로 늘린 자료형에 두개의 정수를 담아놓는다.
		// 인덱스는 어떤 것이 저장되는지
	public:
		__int64 m_EPos;
		size_t EnemyIndex;

		EnemyData() : EnemyIndex(4) {};
		~EnemyData() {};
	};

private:
	BaseEnemy* m_pEnemySet;

	std::map<__int64, size_t> m_EnemyMap;
	std::map<__int64, size_t>::iterator m_FindEnemyIter;
	std::map<__int64, size_t>::iterator m_StartEnemyIter;
	std::map<__int64, size_t>::iterator m_EndEnemyIter;


	std::list<BaseEnemy*> m_OneEnemyList;
	BaseEnemy::Enemy_DataIndex m_EnemyIndex;



public:
	// 몇마리 있는지 반환 
	int Enemy_Index() { return m_EnemyIndex; }

	void Clear();
	std::vector<EnemyData> GetAllEnemyData();
	
private:
	int m_Erase_Size;

public:
	void Set_Enemy(BaseEnemy* _pTileSet);
	void Insert_Enemy(Position _Pos, BaseEnemy::Enemy_DataIndex _Index);
	void SetScreenToEnemy(Position _Pos, BaseEnemy::Enemy_DataIndex _Index);
	void EraseScreenToEnemy(Position _Pos);
	
public:
	MapData_Creator();
	~MapData_Creator();
};

