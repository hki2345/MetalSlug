#pragma once
#include "TheOne.h"

class Animator;
class BaseEnemy : public TheOne
{
public:
	// None은 적이 아닌 경우 -> 핀셋 박을 때 주요
	enum Enemy_DataIndex
	{
		None = -1,
		Walker = 0,
		Bomb,
		Cannon,
		MachineGun,
		SaruBian,
		Tank,
		Bradley,
		End,
		Heli,
	};

protected:
	float m_Time;
	float Die_Time;
	Enemy_DataIndex m_Index;
	Animator* p_Render;

public:
	Enemy_DataIndex& Data_Index() { return m_Index; }

public:
	BaseEnemy();
	~BaseEnemy();
};

