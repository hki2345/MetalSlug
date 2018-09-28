#pragma once
#include "BaseEnemy.h"

class MapData_Creator : public BaseEnemy
{
public:
	class EnemyData
	{
		// ��Ʈ�� 2��� �ø� �ڷ����� �ΰ��� ������ ��Ƴ��´�.
		// �ε����� � ���� ����Ǵ���
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
	// ��� �ִ��� ��ȯ 
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

