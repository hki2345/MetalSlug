#pragma once
#include "BaseEnemy.h"

class Pinset_FixData
{
public:
	Position m_Pos;
	Position m_pos_Dir;
	BaseEnemy::Enemy_DataIndex m_Index;
	size_t m_Num;

public:
	bool operator== (const Pinset_FixData& _Value)
	{
		return (this->m_Pos == _Value.m_Pos &&
			this->m_pos_Dir == _Value.m_pos_Dir &&
			this->m_Index == _Value.m_Index &&
			this->m_Num == _Value.m_Num);
	}

	Pinset_FixData() : m_Pos(Vector2()), m_pos_Dir(Vector2()),
		m_Index(BaseEnemy::Enemy_DataIndex::None), m_Num(0)
	{}
	~Pinset_FixData();
};

