#include "stdafx.h"
#include "MapData_Creator.h"

#include "Enemy_Bomb.h"
#include "Enemy_Walker.h"
#include "Enemy_Cannon.h"
#include "Enemy_Sarubian.h"
#include "Enemy_MachineGun.h"
#include "Enemy_Tank.h"
#include "Enemy_Bradley.h"

#include "ResourceManager.h"

MapData_Creator::MapData_Creator() : m_EnemyIndex(BaseEnemy::End), m_Erase_Size(50)
{
}


MapData_Creator::~MapData_Creator()
{
}

void MapData_Creator::Set_Enemy(BaseEnemy* _pEnemySet)
{
	KAssert(nullptr == _pEnemySet);

	m_pEnemySet = _pEnemySet;
}

// 적의 위치와 그 상태를 저장한다.
// 요부분을 고쳐야함 - 실제 오브젝트가 나오게 꾸민다.
void MapData_Creator::Insert_Enemy(Position _Pos, BaseEnemy::Enemy_DataIndex _Index)
{
	m_FindEnemyIter = m_EnemyMap.find(_Pos.To_Int64());

	if (m_FindEnemyIter != m_EnemyMap.end())
	{
		m_FindEnemyIter->second = _Index;
		return;
	}

	m_EnemyMap.insert(std::map<__int64, size_t>::value_type(_Pos.To_Int64(), (size_t)_Index));
	BaseEnemy* NewEnemy = nullptr;
	// 실제 객체 생성
	switch (_Index)
	{
	case BaseEnemy::Walker:
		NewEnemy = m_MotherOfTheOne->StateOfOne_Create<Enemy_Walker>();
		break;
	case BaseEnemy::Bomb:
		NewEnemy = m_MotherOfTheOne->StateOfOne_Create<Enemy_Bomb>();
		break;
	case BaseEnemy::Cannon:
		NewEnemy = m_MotherOfTheOne->StateOfOne_Create<Enemy_Cannon>();
		break;
	case BaseEnemy::MachineGun:
		NewEnemy = m_MotherOfTheOne->StateOfOne_Create<Enemy_MachineGun>();
		break;
	case BaseEnemy::SaruBian:
		NewEnemy = m_MotherOfTheOne->StateOfOne_Create<Enemy_Sarubian>();
		break;
	case BaseEnemy::Tank:
		NewEnemy = m_MotherOfTheOne->StateOfOne_Create<Enemy_Tank>();
		break;
	case BaseEnemy::Bradley:
		NewEnemy = m_MotherOfTheOne->StateOfOne_Create<Enemy_Bradley>();
		break;
	default:
		break;
	}

	if (nullptr == NewEnemy)
	{
		return;
	}
	NewEnemy->pos(_Pos);
	m_OneEnemyList.push_back(NewEnemy);
}


void MapData_Creator::SetScreenToEnemy(Position _Pos, BaseEnemy::Enemy_DataIndex _Index)
{
	Positionf tempPos = _Pos;
	Insert_Enemy({ (int)tempPos.X, (int)tempPos.Y }, _Index);
}

void MapData_Creator::EraseScreenToEnemy(Position _Pos)
{
	// 해당 반경 내에 있는 적을 지움
	std::list<BaseEnemy*>::iterator StartIter = m_OneEnemyList.begin();
	std::list<BaseEnemy*>::iterator EndIter = m_OneEnemyList.end();

	for (; StartIter !=  EndIter;)
	{
		if ((*StartIter)->pos().X < _Pos.X + m_Erase_Size &&
			(*StartIter)->pos().X > _Pos.X - m_Erase_Size &&
			(*StartIter)->pos().Y < _Pos.Y + m_Erase_Size && 
			(*StartIter)->pos().Y > _Pos.Y - m_Erase_Size)
		{
			(*StartIter)->Death(true);
			StartIter = m_OneEnemyList.erase(StartIter);
		}
		else
		{
			StartIter++;
		}
	}
	
	// 싹 지우고 다시 쓴다 - 이게 더 정확하니까
	m_EnemyMap.clear();

	StartIter = m_OneEnemyList.begin();
	EndIter = m_OneEnemyList.end();

	for (; StartIter != EndIter; StartIter++)
	{
		m_EnemyMap.insert(std::map<__int64, size_t>::value_type(
			(*StartIter)->pos_int().To_Int64(), (*StartIter)->Data_Index()));
	}
}

void MapData_Creator::Clear()
{
	std::list<BaseEnemy*>::iterator StartIter = m_OneEnemyList.begin();
	std::list<BaseEnemy*>::iterator EndIter = m_OneEnemyList.end();

	for (; StartIter != EndIter; StartIter++)
	{
		(*StartIter)->Death(true);
	}
	m_OneEnemyList.clear();
	m_EnemyMap.clear();
}

std::vector<MapData_Creator::EnemyData> MapData_Creator::GetAllEnemyData()
{
	std::vector<MapData_Creator::EnemyData> ReturnData;

	m_StartEnemyIter = m_EnemyMap.begin();
	m_EndEnemyIter = m_EnemyMap.end();

	for (; m_StartEnemyIter != m_EndEnemyIter; m_StartEnemyIter++)
	{
		EnemyData New_EnemyData;

		New_EnemyData.m_EPos = m_StartEnemyIter->first;
		New_EnemyData.EnemyIndex = m_StartEnemyIter->second;
		ReturnData.push_back(New_EnemyData);
	}

	return ReturnData;
}