#include "stdafx.h"
#include "BossMgr.h"


Enemy_Boss* BossMgr::m_MainPlayer = nullptr;

BossMgr::BossMgr()
{
}


BossMgr::~BossMgr()
{
}

Enemy_Boss* BossMgr::MainBoss() {
	return m_MainPlayer;
}

void BossMgr::MainBoss(Enemy_Boss* _MainPlayer) {
	m_MainPlayer = _MainPlayer;
}
