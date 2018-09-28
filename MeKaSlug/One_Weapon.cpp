#include "stdafx.h"
#include "One_Weapon.h"

#include "Collider.h"

One_Weapon::One_Weapon() : m_Run_Speed(1000), m_LiveTime(3), m_ActingTime(0)
{
}


One_Weapon::~One_Weapon()
{
}

void One_Weapon::UpdateCheckLive()
{
	m_ActingTime += DELTATIME;

	// »ç¸Á
	if (m_ActingTime > m_LiveTime)
	{
		// Activate();
		Death(true);
	}
}